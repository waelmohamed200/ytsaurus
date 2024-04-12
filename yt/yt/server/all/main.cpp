#include <yt/yt/server/master/cell_master/program.h>
#include <yt/yt/server/clock_server/cluster_clock/program.h>
#include <yt/yt/server/http_proxy/program.h>
#include <yt/yt/server/rpc_proxy/program.h>
#include <yt/yt/server/job_proxy/program.h>
#include <yt/yt/server/scheduler/program.h>
#include <yt/yt/server/controller_agent/program.h>
#include <yt/yt/server/tools/program.h>
#include <yt/yt/server/node/cluster_node/program.h>
#include <yt/yt/server/exec/program.h>
#include <yt/yt/server/log_tailer/program.h>
#include <yt/yt/server/discovery_server/program.h>
#include <yt/yt/server/timestamp_provider/program.h>
#include <yt/yt/server/master_cache/program.h>
#include <yt/yt/server/cell_balancer/program.h>
#include <yt/yt/server/queue_agent/program.h>
#include <yt/yt/server/query_tracker/program.h>
#include <yt/yt/server/tablet_balancer/program.h>
#include <yt/yt/server/cypress_proxy/program.h>
#include <yt/yt/server/tcp_proxy/program.h>
#include <yt/yt/server/replicated_table_tracker/program.h>

#include <yt/yt/library/program/program.h>

#include <library/cpp/getopt/small/last_getopt_parse_result.h>

using namespace NYT;

////////////////////////////////////////////////////////////////////////////////

NYT::TStringBuilder AllProgramNames;

class TAllProgram
    : public TProgram
{
public:
    TAllProgram()
    {
        // Fake option just to show in --help output.
        Opts_
            .AddFreeArgBinding("program-name", ProgramName_, "Program name to run");
        Opts_
            .SetFreeArgsMax(Opts_.UNLIMITED_ARGS);
        Opts_
            .AddSection("Programs", AllProgramNames.Flush());
    }

private:
    TString ProgramName_;

    void DoRun(const NLastGetopt::TOptsParseResult& /*result*/) override
    {
        Cerr << "Program " << Argv0_ << " is not known" << Endl;
        Exit(EProgramExitCode::OptionsError);
    }
};

template <class T>
void TryProgram(int argc, const char** argv, const TString& nameSuffix)
{
    if (TStringBuf(argv[0]).EndsWith("ytserver-" + nameSuffix)) {
        T().Run(argc, argv);
    }
    AllProgramNames.AppendFormat("ytserver-%v\n", nameSuffix);
}

int main(int argc, const char** argv)
{
    // Shift arguments to handle "program-name" specified in the first argument.
    // Example: ./ytserver-all ytserver-master --help
    if (argc >= 2 &&
        TStringBuf(argv[0]).EndsWith("ytserver-all") &&
        TStringBuf(argv[1]).StartsWith("ytserver-"))
    {
        argc--;
        argv++;
    }

    TryProgram<NCellMaster::TCellMasterProgram>(argc, argv, "master");
    TryProgram<NClusterClock::TClusterClockProgram>(argc, argv, "clock");
    TryProgram<NHttpProxy::THttpProxyProgram>(argc, argv, "http-proxy");
    // TODO(babenko): rename to rpc-proxy
    TryProgram<NRpcProxy::TRpcProxyProgram>(argc, argv, "proxy");
    TryProgram<NClusterNode::TClusterNodeProgram>(argc, argv, "node");
    TryProgram<NJobProxy::TJobProxyProgram>(argc, argv, "job-proxy");
    TryProgram<NExec::TExecProgram>(argc, argv, "exec");
    TryProgram<NTools::TToolsProgram>(argc, argv, "tools");
    TryProgram<NScheduler::TSchedulerProgram>(argc, argv, "scheduler");
    TryProgram<NControllerAgent::TControllerAgentProgram>(argc, argv, "controller-agent");
    TryProgram<NLogTailer::TLogTailerProgram>(argc, argv, "log-tailer");
    TryProgram<NClusterDiscoveryServer::TClusterDiscoveryServerProgram>(argc, argv, "discovery");
    TryProgram<NTimestampProvider::TTimestampProviderProgram>(argc, argv, "timestamp-provider");
    TryProgram<NMasterCache::TMasterCacheProgram>(argc, argv, "master-cache");
    TryProgram<NCellBalancer::TCellBalancerProgram>(argc, argv, "cell-balancer");
    TryProgram<NQueueAgent::TQueueAgentProgram>(argc, argv, "queue-agent");
    TryProgram<NTabletBalancer::TTabletBalancerProgram>(argc, argv, "tablet-balancer");
    TryProgram<NCypressProxy::TCypressProxyProgram>(argc, argv, "cypress-proxy");
    TryProgram<NQueryTracker::TQueryTrackerProgram>(argc, argv, "query-tracker");
    TryProgram<NTcpProxy::TTcpProxyProgram>(argc, argv, "tcp-proxy");
    TryProgram<NReplicatedTableTracker::TReplicatedTableTrackerProgram>(argc, argv, "replicated-table-tracker");
    // Handles auxiliary flags like --version and --build.
    TAllProgram().Run(argc, argv);
}

////////////////////////////////////////////////////////////////////////////////
