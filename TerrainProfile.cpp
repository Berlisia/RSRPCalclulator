#include "TerrainProfile.h"
#include "ui_TerrainProfile.h"
#include <QDebug>
#include <algorithm>

TerrainProfile::TerrainProfile(DataProvider const& p_data,
                               std::shared_ptr<IMapDataProvider> p_mapDataProvider,
                               QWidget* parent)
    : QDialog(parent), ui(new Ui::TerrainProfile), mapDataProvider(std::move(p_mapDataProvider)), dataProvider(p_data)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    QWidget::setWindowTitle("Terrain profile");
}

void TerrainProfile::addPixel(QPointF pixel)
{
    if (pixels.size() == 2)
    {
        pixels.clear();
        vectorOfPiels.clear();
    }
    pixels.push_back(pixel);
}

void TerrainProfile::clearVectorOfPixels()
{
    vectorOfPiels.clear();
}

int TerrainProfile::getPixelsSize()
{
    return pixels.size();
}

QPointF TerrainProfile::getFirstPixel()
{
    return pixels[0];
}

QPointF TerrainProfile::getCurrentPixel()
{
    return currentPixel;
}

void TerrainProfile::setCurrentPixel(QPointF p_currentPixel)
{
    currentPixel = p_currentPixel;
}
TerrainProfile::~TerrainProfile()
{
    delete ui;
}
bool TerrainProfile::isPixelInLine(PixelXY pixel)
{
    auto isCorrectPixel = [pixel](std::pair<int, int> pix){
                            return pixel.getX() == pix.first && pixel.getY() == pix.second;};
    auto iterator = std::find_if(vectorOfPiels.begin(), vectorOfPiels.end(), isCorrectPixel);
    return iterator != vectorOfPiels.end();
}

void TerrainProfile::storeDystansAndValueMapFromResultTable(const std::vector<std::pair<PixelXY, double>>& vectorSrc,
                                            std::vector<std::pair<double, double>>& dystansValueMapTgt)
{
    int pixX = pixels[0].x();
    int pixY = pixels[0].y();
    std::pair<int,int> bsPix(pixX, pixY);
    for (const auto& r : vectorSrc)
    {
        if(isPixelInLine(r.first))
        {
            std::pair<double,double> valuePair(mapDataProvider->coutDistance(bsPix, r.first.getXy()), r.second);
            dystansValueMapTgt.push_back(valuePair);
        }
    }
    std::sort(dystansValueMapTgt.begin(),dystansValueMapTgt.end());
}

void TerrainProfile::saveInFile(const std::vector<std::pair<PixelXY, double>>& vector, std::string name)
{
    std::vector<std::pair<double, double>> dystansValueMap;
    storeDystansAndValueMapFromResultTable(vector,dystansValueMap);

    std::fstream plik;
    plik.open(name.c_str(), std::ios::out);
    if (plik.good() == true)
    {
        for(const auto& value: dystansValueMap)
        {
            plik << value.first << ";" << value.second;
            plik << "\n";
        }
    }
    plik.close();
    qDebug() << "DONE FILE";
}

void TerrainProfile::saveInFileFromCorrectDraw(RadioButtonType radioButton)
{
    switch (radioButton)
    {
    case RadioButtonType::RSRP:
        saveInFile(dataProvider.rsrp.vector, "RSRP_Path.csv");
        break;
    case RadioButtonType::RSSI:
        saveInFile(dataProvider.interferenceLvl, "RSSI_Path.csv");
        break;
    case RadioButtonType::RSRQ:
        saveInFile(dataProvider.rsrq, "RSRQ_Path.csv");
        break;
    case RadioButtonType::SNIR:
        saveInFile(dataProvider.snir, "SNIR_Path.csv");
        break;
    case RadioButtonType::CQI:
        saveInFile(dataProvider.modulation, "CQI_Path.csv");
        break;
    default:
        break;
    }
}

void TerrainProfile::drawTerrainProfile(RadioButtonType radioButton)
{
    std::pair<int, int> pixel1(pixels[0].x(), pixels[0].y());
    std::pair<int, int> pixel2(currentPixel.x(), currentPixel.y());
    vectorOfPiels = mapDataProvider->getVectorOfPixels(pixel1, pixel2, 35);

    saveInFileFromCorrectDraw(radioButton); //zalezy co wlączone
}

void TerrainProfile::drawTerrainProfile(QPixmap& pxMap, const std::vector<std::pair<int, int>>& vector)
{
    QPainter painter(&pxMap);
    painter.setPen(Qt::black);
    double max = findMaxHeightFromVector(vector);
    double min = findMinHeightFromVector(vector);
    double wspolczynnik = max - min;
    wspolczynnik = 300 / wspolczynnik;

    int i = 0;
    for (auto pixel : vector)
    {
        i++;
        double height = mapDataProvider->pixelHeight(pixel);
        painter.drawLine(i, 300, i, (height - min) * wspolczynnik);
    }
    painter.end();
}

void TerrainProfile::drawSignal(QPixmap& pxMap, const std::vector<std::pair<int, int>>& vector)
{
    QPainter painter(&pxMap);
    painter.setPen(Qt::red);

    int i = 0;
    for (auto pixel : vector)
    {
        i++;
        double value = findValueFromData(pixel);
        painter.setPen(Qt::red);
        painter.drawPoint(i, -value);
        painter.drawPoint(i, -value + 1);
        painter.setPen(QColor(255, 255, 255, 100));
        painter.drawLine(i, 300, i, -value);
    }
    painter.end();
}

double TerrainProfile::findMinHeightFromVector(const std::vector<std::pair<int, int>>& vector)
{
    auto biggest = std::min_element(vector.begin(),
                                    vector.end(),
                                    [this](const std::pair<int, int>& l, const std::pair<int, int>& r) {
                                        return mapDataProvider->pixelHeight(l) < mapDataProvider->pixelHeight(r);
                                    });
    return biggest->second;
}

double TerrainProfile::findMaxHeightFromVector(const std::vector<std::pair<int, int>>& vector)
{
    auto biggest = std::max_element(vector.begin(),
                                    vector.end(),
                                    [this](const std::pair<int, int>& l, const std::pair<int, int>& r) {
                                        return mapDataProvider->pixelHeight(l) < mapDataProvider->pixelHeight(r);
                                    });
    return biggest->second;
}

double TerrainProfile::findValueFromData(std::pair<int, int> pixel)
{
    auto finded = std::find_if(dataProvider.rsrp.vector.begin(),
                               dataProvider.rsrp.vector.end(),
                               [pixel](std::pair<PixelXY, double> px) -> bool { return px.first.getXy() == pixel; });
    return finded->second;
}

void TerrainProfile::displayImage(const QPixmap& img)
{
    canvas = new TerrainCanvas(img);
    scene->addItem(canvas);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}
