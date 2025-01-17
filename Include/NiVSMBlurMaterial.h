// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#pragma once
#ifndef NIVSMBLURMATERIAL_H
#define NIVSMBLURMATERIAL_H

#include "NiFragmentMaterial.h"

class NiVSMBlurVertexProgramDescriptor;

class NIMAIN_ENTRY NiVSMBlurMaterial : public NiFragmentMaterial
{
    NiDeclareRTTI;
public:

    // Note: This structure should be kept in sync with the one in
    // NiStandardMaterial

    // This enumeration determines how this material deals with
    // transformations.
    enum TransformType
    {
        // Traditional vertex transformations.
        TRANSFORM_DEFAULT = 0,
        // Skinned vertex transformations wherein bones are chosen from a
        // palette of transforms using per-vertex indices.
        TRANSFORM_SKINNED,
        // This value is reserved and should not be used.
        TRANSFORM_RESERVED,
        // Instanced vertex transformations.
        TRANSFORM_INSTANCED,
        // Maximum transform enum
        TRANSFORM_MAX
    };

    // This enumeration determines how this material deals with texture
    // coordinate transformation..
    enum TexGenOutput
    {
        // Coordinate used as-is.
        TEX_OUT_PASSTHRU = 0,
        // Coordinate has texture transform applied.
        TEX_OUT_TRANSFORM,
        // Coordinate has parallel projection applied.
        TEX_OUT_PARALLEL_PROJECT,
        // Coordinate has perspective projection applied.
        TEX_OUT_PERSPECTIVE_PROJECT,
        // Maximum out enum
        TEX_OUT_MAX
    };

    // Create a default material using the specified material node library.
    // If bAutoCreateCaches is true, a cache is created using the static
    // renderer pointer.
    NiVSMBlurMaterial(NiMaterialNodeLibrary* pkLibrary,
        bool bAutoCreateCaches);

    // Inherited from NiFragmentMaterial. Creates the default fallback
    // functions.
    virtual void AddDefaultFallbacks();

    // Populates the shader cache with a set of fall back shaders. Replacement shaders 
    // are 'fail safe'shaders that can be used when shader compilation can not be performed.
    virtual void AddReplacementShaders();

protected:
    // Inherited from NiFragmentMaterial. Generate the descriptor object that
    // matches the state of this render object. This descriptor will be a
    // NiVSMBlurMaterialDescriptor object.
    virtual bool GenerateDescriptor(const NiRenderObject* pkGeometry,
        const NiPropertyState* pkState,
        const NiDynamicEffectState* pkEffects,
        NiMaterialDescriptor& kMaterialDesc);

    // Inherited from NiFragmentMaterial. This derived implementation controls
    // the wiring of the vertex shader material nodes.
    virtual bool GenerateVertexShadeTree(Context& kContext,
        NiGPUProgramDescriptor* pkDesc);

    // Inherited from NiFragmentMaterial. This derived implementation controls
    // the wiring of the pixel shader material nodes.
    virtual bool GeneratePixelShadeTree(Context& kContext,
        NiGPUProgramDescriptor* pkDesc);

    // This method takes the shader programs generated by the shader
    // generating functions and returns RC_SUCCESS if they were created
    // successfully.
    virtual unsigned int VerifyShaderPrograms(NiGPUProgram* pkVertexShader,
        NiGPUProgram* pkGeometryShader, NiGPUProgram* pkPixelShader);

    // This method facilitates adding a user-defined blur function and blur
    // kernel size. kString is the name of the material node to use for the
    // blur kernel. pkNode is set to this node and pkOutputColor is set to the
    // output of this node. A base texture is added to the shade tree using the
    // pkUV texture set. The blur kernel size is set as an input to the blur
    // node.
    virtual bool InsertTexture(Context& kContext, NiMaterialResource* pkUV,
        NiMaterialResource*& pkOutputColor, NiMaterialNode*& pkNode,
        NiFixedString& kString, unsigned int uiBlurKernel);

    // This method handles the transforming the UV coordinates from their
    // input state to their output state in the vertex shader.
    virtual bool HandleTexGen(Context& kContext,
        NiMaterialResource* pkInputUVResource,
        NiMaterialResource*& pkOutputUVResource,
        const NiFixedString& kMapName, unsigned int uiExtra,
        NiVSMBlurMaterial::TexGenOutput eOutputType);

    // This method deals with generating the world position fragment using the
    // technique specified in the NiVSMBlurMaterial::TransformType
    // enumeration. This method is called when constructing the vertex
    // shade tree.
    virtual bool HandlePositionFragment(
        Context& kContext,
        TransformType eTransType,
        NiMaterialResource*& pkVertWorldPos,
        NiMaterialResource*& pkWorldMatrix);

    // This method applies the view projection matrix to the world position.
    // If requested, this method will generate resources for the computed
    // view position. This method is called when constructing the vertex
    // shade tree.
    virtual bool HandleViewProjectionFragment(Context& kContext,
        bool bForceViewPos, NiMaterialResource* pkVertWorldPos,
        NiMaterialResource*& pkVertOutProjectedPos,
        NiMaterialResource*& pkVertOutViewPos);

    // This method encapsulates the vertex position/normal/binormal/tangent
    // transformation pipeline. If requested, this method will generate the
    // world view vector.
    virtual bool SetupTransformPipeline(Context& kContext,
        NiMaterialResource* pkVertOutProjPos,
        NiVSMBlurVertexProgramDescriptor* pkVertDesc, bool bForceView,
        bool bForceViewPos, NiMaterialResource*& pkWorldPos,
        NiMaterialResource*& pkViewPos, NiMaterialResource*& pkProjectedPos,
        NiMaterialResource*& pkWorldNormal, NiMaterialResource*& pkWorldView);

    // Inherited from NiFragmentMaterial. By default this creates one render
    // pass with an NiStandardPixelProgramDescriptor and an
    // NiStandardVertexProgramDescriptor.
    virtual ReturnCode GenerateShaderDescArray(
        NiMaterialDescriptor* pkMaterialDescriptor,
        RenderPassDescriptor* pkRenderPasses, unsigned int uiMaxCount,
        unsigned int& uiCountAdded);

    // Inherited from NiFragmentMaterial. Creates the NiShader that will be
    // filled in by later methods.
    virtual NiShader* CreateShader(NiMaterialDescriptor* pkDesc);

    // Inherited from NiFragmentMaterial. Configures the shader's packing
    // structures for the requirements of this instance of the material.
    // Note that this method is considered deprecated, and
    // GetVertexInputSemantics should be used instead.
    virtual bool SetupPackingRequirements(NiShader* pkShader,
        NiMaterialDescriptor* pkMaterialDescriptor,
        RenderPassDescriptor* pkRenderPasses, unsigned int uiCount);

    // Shader fallback to be used when all other fallbacks fail. This fall back
    // will resort to using one of the replacement shaders that was inserted into
    // the shader cache at cache creation time. These represent bare bones shaders
    // that are exist to allow an object to be rendered.
    static bool UseVSMReplacementShader(
        NiMaterialDescriptor* pkMaterialDescriptor, ReturnCode eFailedRC,
        unsigned int uiFailedPass, RenderPassDescriptor* pkRenderPasses,
        unsigned int uiMaxCount, unsigned int& uiCount,
        unsigned int& uiFunctionData);

    NiFixedString m_kDescriptorName;
};

NiSmartPointer(NiVSMBlurMaterial);


#endif // NIVSMBLURMATERIAL_H
