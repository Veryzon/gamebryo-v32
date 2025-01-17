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
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

namespace etk
{
//--------------------------------------------------------------------------------------------------
bool SVNErr::Success()
{
    return m_pSvnErr == NULL;
}
//--------------------------------------------------------------------------------------------------
svn_error_t* SVNErr::GetError()
{
    return m_pSvnErr;
}
//--------------------------------------------------------------------------------------------------
SVNErr& SVNErr::operator=(svn_error_t* pSvnErr)
{
    SetError(pSvnErr);
    return *this;
}
//--------------------------------------------------------------------------------------------------
} // end namespace etk
