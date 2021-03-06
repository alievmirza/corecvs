/**
 * \file QTFileLoader.cpp
 * \brief Add Comment Here
 *
 * \date Jun 24, 2010
 * \author alexander
 */
#include <QtGui/QImage>

#include "qtFileLoader.h"

/**
 *  This is a form of dirty hack to be sure that int QT builds loading QT images will always
 *  work without any change of code.
 **/
int QTFileLoader::DUMMY = 1;//QTFileLoader::registerMyself();

QTFileLoader::QTFileLoader()
{
    // TODO Auto-generated constructor stub

}

QTFileLoader::~QTFileLoader()
{
    // TODO Auto-generated destructor stub
}

G12Buffer* QTFileLoader::load(string name)
{
    QString qtName = QString::fromStdString(name);
    QImage image(qtName);

    if (image.isNull())
        return NULL;

    G12Buffer *result = new G12Buffer(image.height(), image.width(), false);

    /**
     * TODO: Make this faster using .bits() method.
     * So far don't want to mess with possible image formats
     *
     */
    for (int i = 0; i < image.height(); i++)
    {
        for (int j = 0; j < image.width(); j++)
        {
            QRgb pixel = image.pixel(j,i);
            // Do conversion without qGray to possibly save 9-th bit
            uint16_t gray = (11 * qRed(pixel) + 16 * qGreen(pixel) + 5 * qBlue(pixel)) >> 1;
            result->element(i,j) = gray;
        }
    }

    return result;
}

bool QTFileLoader::acceptsFile(string /*name*/)
{
    return true;
}


RGB24Buffer *QTFileLoader::RGB24BufferFromQImage(QImage *image)
{
    if (image == NULL)
        return NULL;

    RGB24Buffer *result = new RGB24Buffer(image->height(), image->width(), false);

    /**
     * TODO: Make this faster using .bits() method.
     * So far don't want to mess with possible image formats
     *
     */
    for (int i = 0; i < image->height(); i++)
    {
        for (int j = 0; j < image->width(); j++)
        {
            QRgb pixel = image->pixel(j,i);
            result->element(i,j) = RGBColor(qRed(pixel), qGreen(pixel), qBlue(pixel));
        }
    }

    return result;
}
