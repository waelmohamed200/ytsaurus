#pragma once

#include "public.h"

#include <yt/yt/server/lib/misc/disk_change_checker.h>

#include <yt/yt/ytlib/api/native/public.h>
#include <yt/yt/ytlib/misc/public.h>

#include <yt/yt/library/auth_server/public.h>

#include <yt/yt/library/monitoring/public.h>

#include <yt/yt/client/node_tracker_client/public.h>

#include <yt/yt/library/coredumper/public.h>

#include <yt/yt/library/containers/public.h>

#include <yt/yt/library/tracing/jaeger/public.h>

#include <yt/yt/core/bus/public.h>

#include <yt/yt/core/concurrency/public.h>

#include <yt/yt/core/misc/atomic_object.h>
#include <yt/yt/core/misc/public.h>

#include <yt/yt/core/rpc/grpc/public.h>

#include <yt/yt/core/http/public.h>

#include <yt/yt/core/ytree/public.h>

namespace NYT::NRpcProxy {

////////////////////////////////////////////////////////////////////////////////

class TBootstrap
{
public:
    TBootstrap(
        TProxyConfigPtr config,
        NYTree::INodePtr configNode);
    ~TBootstrap();

    void Run();

private:
    const TProxyConfigPtr Config_;
    const NYTree::INodePtr ConfigNode_;

    const NConcurrency::TActionQueuePtr ControlQueue_;
    const NConcurrency::IThreadPoolPtr WorkerPool_;
    const NConcurrency::IPollerPtr HttpPoller_;

    NMonitoring::TMonitoringManagerPtr MonitoringManager_;
    NBus::IBusServerPtr BusServer_;
    NBus::IBusServerPtr TvmOnlyBusServer_;
    IApiServicePtr ApiService_;
    IApiServicePtr TvmOnlyApiService_;
    NRpc::IServicePtr DiscoveryService_;
    NRpc::IServerPtr RpcServer_;
    NRpc::IServerPtr TvmOnlyRpcServer_;
    NRpc::IServerPtr GrpcServer_;
    NHttp::IServerPtr HttpServer_;
    NCoreDump::ICoreDumperPtr CoreDumper_;

    NApi::NNative::IConnectionPtr Connection_;
    NRpc::IAuthenticatorPtr NativeAuthenticator_;
    NApi::NNative::IClientPtr RootClient_;
    NAuth::IAuthenticationManagerPtr AuthenticationManager_;
    NAuth::IAuthenticationManagerPtr TvmOnlyAuthenticationManager_;
    NRpcProxy::TRpcProxyHeapUsageProfilerPtr RpcProxyHeapUsageProfiler_;
    NRpcProxy::IProxyCoordinatorPtr ProxyCoordinator_;
    NTracing::TSamplerPtr TraceSampler_;
    NNodeTrackerClient::TAddressMap LocalAddresses_;
    IDynamicConfigManagerPtr DynamicConfigManager_;
    IBundleDynamicConfigManagerPtr BundleDynamicConfigManager_;
    IAccessCheckerPtr AccessChecker_;

    INodeMemoryTrackerPtr MemoryUsageTracker_;

    NContainers::IDiskManagerProxyPtr DiskManagerProxy_;
    NContainers::TDiskInfoProviderPtr DiskInfoProvider_;
    TDiskChangeCheckerPtr DiskChangeChecker_;

    void DoRun();

    void OnDynamicConfigChanged(
        const TProxyDynamicConfigPtr& /*oldConfig*/,
        const TProxyDynamicConfigPtr& newConfig);

    void OnBundleDynamicConfigChanged(
        const TBundleProxyDynamicConfigPtr& /*oldConfig*/,
        const TBundleProxyDynamicConfigPtr& newConfig);

    const IInvokerPtr& GetWorkerInvoker() const;
    const IInvokerPtr& GetControlInvoker() const;

    void ReconfigureMemoryLimits(const TProxyMemoryLimitsPtr& memoryLimits);

    void ReconfigureConnection(
        const TProxyDynamicConfigPtr& dynamicConfig,
        const TBundleProxyDynamicConfigPtr& bundleConfig);
};

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NRpcProxy
