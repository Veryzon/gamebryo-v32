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

#ifndef NISCENEGRAPHUPDATEOBJECT_H
#define NISCENEGRAPHUPDATEOBJECT_H

#include "NiSceneGraphUpdateServiceLibType.h"
#include "NiSceneGraphUpdateObjectId.h"

#include <NiObject.h>

/**
    This class associates a NiObject with a NiSceneGraphUpdateObjectId

    This class is used by the NiSceneGraphUpdate class to syncrhonize scene graph objects
    between an editor and viewer application. The editor is responsible for generating the
    unique ID. The IDs are used to identify objects to be updated or removed in
    the viewers.
*/
class NISCENEGRAPHUPDATESERVICE_ENTRY NiSceneGraphUpdateObject : public NiObject
{
    friend class NiSceneGraphUpdate;
public:

    /**
        Initialize object

        @param kId Unique ID generated by the editor
    */
    NiSceneGraphUpdateObject(const NiSceneGraphUpdateObjectId& kId);

    /// Destroy object and set smart pointer to NiObject to NULL
    virtual ~NiSceneGraphUpdateObject();

    /// Returns the unique ID that identifies the NiObject
    inline const NiSceneGraphUpdateObjectId& GetId() const;

    /// Returns a pointer to the NiObject
    inline NiObject* GetObject();

protected:
    void SetObject(NiObject* pkObject);
    NiSceneGraphUpdateObjectId m_kId;
    NiObjectPtr m_spObject;
private:

    NiSceneGraphUpdateObject();
};
NiSmartPointer(NiSceneGraphUpdateObject);

//--------------------------------------------------------------------------------------------------

#include "NiSceneGraphUpdateObject.inl"

#endif // #ifndef NISCENEGRAPHUPDATEOBJECT_H