#include <gtest/gtest.h>
#include <model/simulation.h>
#include <model/document.h>

#include <QDebug>

config::Tools::Tool tool1mmPass()
{
	config::Tools::Tool tool {"tool", YAML::Node()};
	tool.general().depthPerCut() = 1.0f;

	return tool;
}

static const config::Tools::Tool tool(tool1mmPass());
static const config::Profiles::Profile::Gcode gcode{"gcode", YAML::Node()};
static const config::Profiles::Profile profile{"profile", YAML::Node()};

model::Document::UPtr documentFromPolylines(geometry::Polyline &&polyline, const model::PathSettings &settings)
{
	model::Path::UPtr path = std::make_unique<model::Path>(std::move(polyline), "", settings);

	model::Path::ListUPtr paths;
	paths.push_back(std::move(path));

	model::Layer::UPtr layer = std::make_unique<model::Layer>("layer", std::move(paths));

	model::Layer::ListUPtr layers;
	layers.push_back(std::move(layer));
	model::Task::UPtr task = std::make_unique<model::Task>(std::move(layers));
	return std::make_unique<model::Document>(std::move(task), tool, profile);
}

TEST(SimulationTest, shouldHasMultiLayerDepth)
{
	const int nbCut = 10;
	const geometry::Bulge bulge(QVector2D(1, 0), QVector2D(1, 1), 0);
	geometry::Polyline polyline({bulge});

	const model::PathSettings settings{10, 10, 10, nbCut - 1};
	model::Document::UPtr document = documentFromPolylines(std::move(polyline), settings);

	model::Simulation simulation(*document);
	const geometry::Point3DList points = simulation.approximatedPathToLines(0.001);

	const int exceptedNbPoints = 2 /* retract + start */ + 2 * nbCut /* cut */ + 2 /* retract and home */;
	EXPECT_EQ(exceptedNbPoints, points.size());
}

TEST(SimulationTest, shouldNotContainsDuplicatePoints)
{
	const int nbCut = 10;
	const geometry::Bulge bulge(QVector2D(1, 0), QVector2D(1, 1), 1);
	const geometry::Bulge bulge2(QVector2D(1, 1), QVector2D(-1, 1), -0.5);
	geometry::Polyline polyline({bulge});

	const model::PathSettings settings{10, 10, 10, nbCut - 1};
	model::Document::UPtr document = documentFromPolylines(std::move(polyline), settings);

	model::Simulation simulation(*document);
	const geometry::Point3DList points = simulation.approximatedPathToLines(0.001);

	for (int i = 0, size = points.size() - 1; i < size; ++i) {
		EXPECT_NE(points[i], points[i + 1]);
	}
}

