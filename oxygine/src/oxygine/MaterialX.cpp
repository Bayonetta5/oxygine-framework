#include "MaterialX.h"
#include "STDRenderer.h"
#include "core/UberShaderProgram.h"
#include "STDRenderer.h"

namespace oxygine
{
    spMaterialX currentMat;

    bool STDMatData::isSame(const STDMatData& b) const
    {
        if (_base != b._base)
            return false;
        if (_alpha != b._alpha)
            return false;
        if (_blend != b._blend)
            return false;
        if (_flags != b._flags)
            return false;
        if (us != b.us)
            return false;
        return true;
    }

    STDMatData::STDMatData() : _blend(blend_alpha), _flags(0), us(&STDRenderer::uberShader)
    {

    }

    void STDMatData::init(size_t& hash) const
    {
        hash_combine(hash, _base.get());
        hash_combine(hash, _alpha.get());
        hash_combine(hash, (int)_blend);
        hash_combine(hash, _flags);
        hash_combine(hash, us);
    }

    void STDMatData::apply()
    {
        STDRenderer* r = STDRenderer::getCurrent();
        r->setUberShaderProgram(us);
        r->setShaderFlags(_flags);
        r->setTextureNew(UberShaderProgram::SAMPLER_BASE, _base);
        r->setTextureNew(UberShaderProgram::SAMPLER_ALPHA, _alpha);
        r->setBlendMode(_blend);
    }

    MaterialX::MaterialX(const MaterialX& other)
    {
        _hash = other._hash;
        _compare = other._compare;
    }

    MaterialX::MaterialX(compare cmp) : _hash(0), _compare(cmp)
    {

    }

    MaterialX::MaterialX() : _hash(0)
    {

    }

    oxygine::MaterialX& MaterialX::operator=(const MaterialX& r)
    {
        _compare = r._compare;
        _hash = r._hash;
        return *this;
    }

}