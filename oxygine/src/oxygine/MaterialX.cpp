#include "MaterialX.h"
#include "STDRenderer.h"
#include "core/UberShaderProgram.h"
#include "STDRenderer.h"

namespace oxygine
{
    spMaterialX currentMat;

    bool STDMatData::operator==(const STDMatData& b) const
    {
        if (_base != b._base)
            return false;
        if (_alpha != b._alpha)
            return false;
        if (_blend != b._blend)
            return false;
        if (_flags != b._flags)
            return false;
        return true;
    }

    STDMatData::STDMatData() : _blend(blend_alpha), _flags(0)
    {

    }

    void STDMatData::init(size_t& hash)
    {
        hash_combine(hash, _base.get());
        hash_combine(hash, _alpha.get());
        hash_combine(hash, _blend);
        hash_combine(hash, _flags);
    }

    void STDMatData::apply()
    {
        STDRenderer::getCurrent()->setShaderFlags(_flags);
        STDRenderer::getCurrent()->setTextureNew(UberShaderProgram::SAMPLER_BASE, _base);
        STDRenderer::getCurrent()->setTextureNew(UberShaderProgram::SAMPLER_ALPHA, _alpha);
        STDRenderer::getCurrent()->setBlendMode(_blend);
    }

}