/**
 * \file bufferFactory.cpp
 * \brief Holds the implementation of the factory for the loadable buffer
 *
 * \ingroup cppcorefiles
 * \date Jun 22, 2010
 * \author alexander
 */
#include "bufferFactory.h"
#include "ppmLoader.h"
#include "rawLoader.h"
#include "bmpLoader.h"

namespace corecvs {

CountedPtr<BufferFactory> BufferFactory::sThis;

//static
BufferFactory* BufferFactory::getInstance()
{
    ASSERT_TRUE(sThis.get() != NULL, "Out of memory!");

    if (sThis.get()->mLoaders.size() == 0)
    {
        sThis.get()->registerLoader(new PPMLoader());
        sThis.get()->registerLoader(new RAWLoader());
        sThis.get()->registerLoader(new BMPLoader());
    }
    return sThis.get();
}

G12Buffer *BufferFactory::loadG12Bitmap(string name)
{
    vector<BufferLoader<G12Buffer> *>::iterator it;
    for (it = mLoaders.begin(); it != mLoaders.end(); it++)
    {
        if (!((*it)->acceptsFile(name)))
            continue;

        G12Buffer *result = (*it)->load(name);
        if (result != NULL)
            return result;
    }

    return NULL;
}

G12Buffer *BufferFactory::loadG16Bitmap(string name)
{
    if (name.rfind(".pgm") != string::npos)
    {
        return PPMLoader().g16BufferCreateFromPPM(name);
    }

    G12Buffer *result = NULL;
    FILE *In = NULL;
    uint32_t h = 0;
    uint32_t w = 0;
    uint16_t d = 0;
    int read = 0;


    In = fopen(name.c_str(), "rb");
    if (In == NULL)
    {
        goto exit;
    }

    read = fread(&h, sizeof(uint32_t), 1, In);
    if (read != 1) {
        goto exit;
    }
    read = fread(&w, sizeof(uint32_t), 1, In);
    if (read != 1)
    {
        goto exit;
    }

    if (h > 2000 || w > 2000)
    {
        goto exit;
    }
    result = new G12Buffer(h,w);

    for (uint32_t i = 0; i < h; ++i) {
        for (uint32_t j = 0; j < w; ++j) {
            read = fread(&d, sizeof(uint16_t), 1, In);
            if (read != 1)
            {
                goto exit;
            }
            result->element(i,j) = d;
        }
    }

exit:
    if (In != NULL)
    {
        fclose(In);
    }
    return result;
}

BufferFactory::~BufferFactory()
{
    // delete all registered loaders
    vector<BufferLoader<G12Buffer> *>::iterator it;
    for (it = mLoaders.begin(); it != mLoaders.end(); it++)
    {
        delete_safe (*it);
    }
    mLoaders.clear();
    //printf("BufferFactory has been destroyed.\n");
}

} //namespace corecvs
