#include "MaterialX.h"
#include "STDRenderer.h"
#include "core/UberShaderProgram.h"
#include "STDRenderer.h"

namespace oxygine
{
    spMaterialX MaterialX::current;

    bool STDMaterialX::cmp(const STDMaterialX& a, const STDMaterialX& b)
    {
        if (a._base != b._base)
            return false;
        if (a._alpha != b._alpha)
            return false;
        if (a._blend != b._blend)
            return false;
        if (a._flags != b._flags)
            return false;
        if (a._uberShader != b._uberShader)
            return false;
        return true;
    }

    void STDMaterialX::init()
    {
        _blend = blend_premultiplied_alpha;
        _flags = 0;
        _uberShader = &STDRenderer::uberShader;
    }

    void STDMaterialX::rehash(size_t& hash) const
    {
        hash_combine(hash, _base.get());
        hash_combine(hash, _alpha.get());
        hash_combine(hash, (int)_blend);
        hash_combine(hash, _flags);
        hash_combine(hash, _uberShader);
    }

    void STDMaterialX::xapply()
    {
        STDRenderer* r = STDRenderer::getCurrent();
        r->setUberShaderProgram(_uberShader);
        r->setShaderFlags(_flags);
        r->setTextureNew(UberShaderProgram::SAMPLER_BASE, _base);
        r->setTextureNew(UberShaderProgram::SAMPLER_ALPHA, _alpha);
        r->setBlendMode(_blend);
    }

    void STDMaterialX::xflush()
    {
        STDRenderer::getCurrent()->flush();
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

    void MaterialX::render(const AffineTransform& tr, const Color& c, const RectF& src, const RectF& dest)
    {
        STDRenderer::getCurrent()->setTransform(tr);
        STDRenderer::getCurrent()->draw(c, src, dest);
    }

    void MaterialX::render(const Color& c, const RectF& src, const RectF& dest)
    {
        STDRenderer::getCurrent()->draw(c, src, dest);
    }

    void MaterialX::apply()
    {
        if (current != this)
        {
            if (current)
                current->flush();
            xapply();
            current = this;
        }
    }


    void MaterialX::flush()
    {
        xflush();
    }

    oxygine::MaterialX& MaterialX::operator=(const MaterialX& r)
    {
        _compare = r._compare;
        _hash = r._hash;
        return *this;
    }

}