#ifndef SURFACEGRAPH_H
#define SURFACEGRAPH_H

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtWidgets/QSlider>
#include <QtWidgets/QCheckBox>

using namespace QtDataVisualization;

class SurfaceGraph : public QObject
{
    Q_OBJECT
public:
    explicit SurfaceGraph(Q3DSurface *surface, QCheckBox *borderCheckBox);
    ~SurfaceGraph();

    void enableHeightMapModel(bool enable);
    void enableSqrtSinModel(bool enable);

    void toggleModeNone() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionNone); }
    void toggleModeItem() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionItem); }

    void setBlackToYellowGradient();
    void setGreenToRedGradient();

    void setAxisMinSliderX(QSlider *slider) { m_axisMinSliderX = slider; }
    void setAxisMaxSliderX(QSlider *slider) { m_axisMaxSliderX = slider; }
    void setAxisMinSliderZ(QSlider *slider) { m_axisMinSliderZ = slider; }
    void setAxisMaxSliderZ(QSlider *slider) { m_axisMaxSliderZ = slider; }

    void adjustXMin(int min);
    void adjustXMax(int max);
    void adjustZMin(int min);
    void adjustZMax(int max);

public Q_SLOTS:
    void changeTheme(int theme);
    void viewGrid(bool enable);
    void viewLabelBorder(bool enable);
    void viewLabel(bool enable);

private:
    Q3DSurface *m_graph;
    QHeightMapSurfaceDataProxy *m_heightMapProxy;
    QSurfaceDataProxy *m_sqrtSinProxy;
    QSurface3DSeries *m_heightMapSeries;
    QSurface3DSeries *m_sqrtSinSeries;

    QSlider *m_axisMinSliderX;
    QSlider *m_axisMaxSliderX;
    QSlider *m_axisMinSliderZ;
    QSlider *m_axisMaxSliderZ;
    float m_rangeMinX;
    float m_rangeMinZ;
    float m_stepX;
    float m_stepZ;
    int m_heightMapWidth;
    int m_heightMapHeight;

    void setAxisXRange(float min, float max);
    void setAxisZRange(float min, float max);
    void fillSqrtSinProxy();
};

#endif // SURFACEGRAPH_H
