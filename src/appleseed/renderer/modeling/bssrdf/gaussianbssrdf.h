
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2015-2017 Francois Beaune, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_RENDERER_MODELING_BSSRDF_GAUSSIANBSSRDF_H
#define APPLESEED_RENDERER_MODELING_BSSRDF_GAUSSIANBSSRDF_H

// appleseed.renderer headers.
#include "renderer/global/globaltypes.h"
#include "renderer/modeling/bssrdf/bssrdf.h"
#include "renderer/modeling/bssrdf/ibssrdffactory.h"
#include "renderer/modeling/bssrdf/separablebssrdf.h"
#include "renderer/modeling/input/inputarray.h"

// appleseed.foundation headers.
#include "foundation/platform/compiler.h"

// appleseed.main headers.
#include "main/dllsymbol.h"

// Forward declarations.
namespace foundation    { class Dictionary; }
namespace foundation    { class DictionaryArray; }
namespace renderer      { class ParamArray; }

namespace renderer
{

//
// Gaussian BSSRDF input values.
//

APPLESEED_DECLARE_INPUT_VALUES(GaussianBSSRDFInputValues)
{
    float           m_weight;
    Spectrum        m_reflectance;
    float           m_reflectance_multiplier;
    Spectrum        m_mfp;
    float           m_mfp_multiplier;
    float           m_ior;
    float           m_fresnel_weight;

    struct Precomputed
    {
        Spectrum    m_k;
        Spectrum    m_channel_pdf;
    };

    Precomputed                     m_precomputed;
    SeparableBSSRDF::InputValues    m_base_values;
};


//
// Gaussian BSSRDF factory.
//

class APPLESEED_DLLSYMBOL GaussianBSSRDFFactory
  : public IBSSRDFFactory
{
  public:
    // Delete this instance.
    void release() override;

    // Return a string identifying this BSSRDF model.
    const char* get_model() const override;

    // Return metadata for this BSSRDF model.
    foundation::Dictionary get_model_metadata() const override;

    // Return metadata for the inputs of this BSSRDF model.
    foundation::DictionaryArray get_input_metadata() const override;

    // Create a new BSSRDF instance.
    foundation::auto_release_ptr<BSSRDF> create(
        const char*         name,
        const ParamArray&   params) const override;
};

}       // namespace renderer

#endif  // !APPLESEED_RENDERER_MODELING_BSSRDF_GAUSSIANBSSRDF_H
