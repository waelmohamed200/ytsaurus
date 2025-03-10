#pragma once

#include <yt/yt/client/node_tracker_client/public.h>

#include <yt/yt/client/object_client/public.h>

#include <yt/yt/client/sequoia_client/public.h>

#include <yt/yt/client/table_client/public.h>

#include <yt/yt/core/ypath/public.h>

namespace NYT::NSequoiaClient {

////////////////////////////////////////////////////////////////////////////////

DEFINE_ENUM(ESequoiaTable,
    (PathToNodeId)
    (NodeIdToPath)
    (ChunkReplicas)
    (LocationReplicas)
    (ChildNode)
    (Transactions)
    (TransactionDescendants)
    (TransactionReplicas)
    (DependentTransactions)
);

namespace NRecords {

struct TPathToNodeId;
struct TNodeIdToPath;
struct TChildNode;

struct TChunkReplicas;
struct TLocationReplicas;

struct TTransactions;
struct TTransactionDescendants;
struct TTransactionReplicas;
struct TDependentTransactions;

} // namespace NRecords

////////////////////////////////////////////////////////////////////////////////

DECLARE_REFCOUNTED_STRUCT(ISequoiaClient)
DECLARE_REFCOUNTED_STRUCT(ISequoiaTransaction)

DECLARE_REFCOUNTED_STRUCT(ILazySequoiaClient)

////////////////////////////////////////////////////////////////////////////////

YT_DEFINE_STRONG_TYPEDEF(TMangledSequoiaPath, NYPath::TYPath);

class TYPath;
class TYPathBuf;

////////////////////////////////////////////////////////////////////////////////

struct ISequoiaTransactionActionOrderer
{
    virtual int GetPriority(TStringBuf actionType) const = 0;
};

////////////////////////////////////////////////////////////////////////////////

struct TSequoiaTransactionSequencingOptions;

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NSequoiaClient
