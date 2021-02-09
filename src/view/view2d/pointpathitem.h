#pragma once

#include <view/view2d/basicpathitem.h>
#include <view/view2d/offsetedpolylinepathitem.h>

namespace View::View2d
{

/** @brief Graphics path item meant to display polylines with length.
 */
class PointPathItem : public BasicPathItem
{
	Q_OBJECT;

private:
	QVector2D m_point;
	QPainterPath m_shapePath;

	QPainterPath shapePath() const;

public:
	explicit PointPathItem(Model::Path *path);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

	QPainterPath shape() const override;
	QRectF boundingRect() const override;
};

}
