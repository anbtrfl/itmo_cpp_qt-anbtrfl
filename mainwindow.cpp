#include "mainwindow.h"
#include "surfacegraph.h"


mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent)
{
    QtDataVisualization::Q3DSurface *graph = new QtDataVisualization::Q3DSurface();
    QWidget *container = QWidget::createWindowContainer(graph);

    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);

    widget->setWindowTitle(QStringLiteral("Surface example"));

    QGroupBox *modelGroupBox = new QGroupBox(QStringLiteral("Model"));

    QRadioButton *sqrtSinModelRB = new QRadioButton(widget);
    sqrtSinModelRB->setText(QStringLiteral("Sqrt && Sin"));
    sqrtSinModelRB->setChecked(false);

    QRadioButton *heightMapModelRB = new QRadioButton(widget);
    heightMapModelRB->setText(QStringLiteral("Height Map"));
    heightMapModelRB->setChecked(false);

    QVBoxLayout *modelVBox = new QVBoxLayout;
    modelVBox->addWidget(sqrtSinModelRB);
    modelVBox->addWidget(heightMapModelRB);
    modelGroupBox->setLayout(modelVBox);

    QGroupBox *selectionGroupBox = new QGroupBox(QStringLiteral("Selection Mode"));

    QRadioButton *modeNoneRB = new QRadioButton(widget);
    modeNoneRB->setText(QStringLiteral("No selection"));
    modeNoneRB->setChecked(false);

    QRadioButton *modeItemRB = new QRadioButton(widget);
    modeItemRB->setText(QStringLiteral("Item"));
    modeItemRB->setChecked(false);

    QVBoxLayout *selectionVBox = new QVBoxLayout;
    selectionVBox->addWidget(modeNoneRB);
    selectionVBox->addWidget(modeItemRB);
    selectionGroupBox->setLayout(selectionVBox);

    QGroupBox *viewGroupBox = new QGroupBox(QStringLiteral("View Mode"));

    QCheckBox *modeGrid = new QCheckBox(widget);
    modeGrid->setText(QStringLiteral("Show grid"));
    modeGrid->setChecked(true);

    QCheckBox *modeLabel = new QCheckBox(widget);
    modeLabel->setText(QStringLiteral("Show label"));
    modeLabel->setChecked(true);

    QCheckBox *modeLabelBorder = new QCheckBox(widget);
    modeLabelBorder->setText(QStringLiteral("Show label borders"));
    modeLabelBorder->setChecked(false);

    QVBoxLayout *viewVBox = new QVBoxLayout;
    viewVBox->addWidget(modeGrid);
    viewVBox->addWidget(modeLabel);
    viewVBox->addWidget(modeLabelBorder);
    viewGroupBox->setLayout(viewVBox);


    QSlider *axisMinSliderX = new QSlider(Qt::Horizontal, widget);
    axisMinSliderX->setMinimum(0);
    axisMinSliderX->setTickInterval(1);
    axisMinSliderX->setEnabled(true);
    QSlider *axisMaxSliderX = new QSlider(Qt::Horizontal, widget);
    axisMaxSliderX->setMinimum(1);
    axisMaxSliderX->setTickInterval(1);
    axisMaxSliderX->setEnabled(true);
    QSlider *axisMinSliderZ = new QSlider(Qt::Horizontal, widget);
    axisMinSliderZ->setMinimum(0);
    axisMinSliderZ->setTickInterval(1);
    axisMinSliderZ->setEnabled(true);
    QSlider *axisMaxSliderZ = new QSlider(Qt::Horizontal, widget);
    axisMaxSliderZ->setMinimum(1);
    axisMaxSliderZ->setTickInterval(1);
    axisMaxSliderZ->setEnabled(true);

    QGroupBox *colorGroupBox = new QGroupBox(QStringLiteral("Custom gradient"));

    QLinearGradient grBtoY(0, 0, 1, 100);
    grBtoY.setColorAt(1.0, Qt::black);
    grBtoY.setColorAt(0.67, Qt::blue);
    grBtoY.setColorAt(0.33, Qt::red);
    grBtoY.setColorAt(0.0, Qt::yellow);
    QPixmap pm(24, 100);
    QPainter pmp(&pm);
    pmp.setBrush(QBrush(grBtoY));
    pmp.setPen(Qt::NoPen);
    pmp.drawRect(0, 0, 24, 100);
    QPushButton *gradientBtoYPB = new QPushButton(widget);
    gradientBtoYPB->setIcon(QIcon(pm));
    gradientBtoYPB->setIconSize(QSize(24, 100));

    QLinearGradient grGtoR(0, 0, 1, 100);
    grGtoR.setColorAt(1.0, Qt::darkGreen);
    grGtoR.setColorAt(0.5, Qt::yellow);
    grGtoR.setColorAt(0.2, Qt::red);
    grGtoR.setColorAt(0.0, Qt::darkRed);
    pmp.setBrush(QBrush(grGtoR));
    pmp.drawRect(0, 0, 24, 100);
    QPushButton *gradientGtoRPB = new QPushButton(widget);
    gradientGtoRPB->setIcon(QIcon(pm));
    gradientGtoRPB->setIconSize(QSize(24, 100));

    QHBoxLayout *colorHBox = new QHBoxLayout;
    colorHBox->addWidget(gradientBtoYPB);
    colorHBox->addWidget(gradientGtoRPB);
    colorGroupBox->setLayout(colorHBox);

    vLayout->addWidget(modelGroupBox);
    vLayout->addWidget(selectionGroupBox);
    vLayout->addWidget(viewGroupBox);
    vLayout->addWidget(new QLabel(QStringLiteral("Column range")));
    vLayout->addWidget(axisMinSliderX);
    vLayout->addWidget(axisMaxSliderX);
    vLayout->addWidget(new QLabel(QStringLiteral("Row range")));
    vLayout->addWidget(axisMinSliderZ);
    vLayout->addWidget(axisMaxSliderZ);
    vLayout->addWidget(colorGroupBox);

    widget->show();

    SurfaceGraph *modifier = new SurfaceGraph(graph, modeLabelBorder);

    QObject::connect(heightMapModelRB, &QRadioButton::toggled,
                     modifier, &SurfaceGraph::enableHeightMapModel);

    QObject::connect(sqrtSinModelRB, &QRadioButton::toggled,
                     modifier, &SurfaceGraph::enableSqrtSinModel);

    QObject::connect(modeNoneRB, &QRadioButton::toggled,
                     modifier, &SurfaceGraph::toggleModeNone);

    QObject::connect(modeItemRB,  &QRadioButton::toggled,
                     modifier, &SurfaceGraph::toggleModeItem);

    QObject::connect(modeGrid, SIGNAL(toggled(bool)),
                     modifier, SLOT(viewGrid(bool)));

    QObject::connect(modeLabel, SIGNAL(toggled(bool)),
                     modifier, SLOT(viewLabel(bool)));

    QObject::connect(modeLabel, SIGNAL(toggled(bool)),
                     modifier, SLOT(modeLabelBorder->setCheckable(bool)));

    QObject::connect(modeLabelBorder, SIGNAL(toggled(bool)),
                     modifier, SLOT(viewLabelBorder(bool)));

    QObject::connect(axisMinSliderX, &QSlider::valueChanged,
                     modifier, &SurfaceGraph::adjustXMin);

    QObject::connect(axisMaxSliderX, &QSlider::valueChanged,
                     modifier, &SurfaceGraph::adjustXMax);

    QObject::connect(axisMinSliderZ, &QSlider::valueChanged,
                     modifier, &SurfaceGraph::adjustZMin);

    QObject::connect(axisMaxSliderZ, &QSlider::valueChanged,
                     modifier, &SurfaceGraph::adjustZMax);

    QObject::connect(gradientBtoYPB, &QPushButton::pressed,
                     modifier, &SurfaceGraph::setBlackToYellowGradient);

    QObject::connect(gradientGtoRPB, &QPushButton::pressed,
                     modifier, &SurfaceGraph::setGreenToRedGradient);

    modifier->setAxisMinSliderX(axisMinSliderX);
    modifier->setAxisMaxSliderX(axisMaxSliderX);
    modifier->setAxisMinSliderZ(axisMinSliderZ);
    modifier->setAxisMaxSliderZ(axisMaxSliderZ);

    sqrtSinModelRB->setChecked(true);
    modeItemRB->setChecked(true);
}

mainwindow::~mainwindow()
{
    delete parent();
}
