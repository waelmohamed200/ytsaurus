#pragma once

#include <yt/yt/ytlib/cypress_client/public.h>

#include <yt/yt/core/misc/public.h>

namespace NYT::NCypressProxy {

////////////////////////////////////////////////////////////////////////////////

struct IBootstrap;

DECLARE_REFCOUNTED_STRUCT(IObjectService)

DECLARE_REFCOUNTED_CLASS(TDynamicConfigManager)

////////////////////////////////////////////////////////////////////////////////

DECLARE_REFCOUNTED_CLASS(TObjectServiceDynamicConfig)
DECLARE_REFCOUNTED_CLASS(TCypressProxyDynamicConfig)

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NCypressProxy
