// Generated by the gRPC protobuf plugin.
// If you make any local change, they will be lost.
// source: authentication_service.proto
#ifndef GRPC_authentication_5fservice_2eproto__INCLUDED
#define GRPC_authentication_5fservice_2eproto__INCLUDED

#include "authentication_service.pb.h"

#include <grpc++/support/async_stream.h>
#include <grpc++/impl/rpc_method.h>
#include <grpc++/impl/proto_utils.h>
#include <grpc++/impl/service_type.h>
#include <grpc++/support/async_unary_call.h>
#include <grpc++/support/status.h>
#include <grpc++/support/stub_options.h>
#include <grpc++/support/sync_stream.h>

namespace grpc {
class CompletionQueue;
class Channel;
class RpcService;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace authentication {

class Login GRPC_FINAL {
 public:
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status LoginCheck(::grpc::ClientContext* context, const ::authentication::LoginRequest& request, ::authentication::LoginReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::authentication::LoginReply>> AsyncLoginCheck(::grpc::ClientContext* context, const ::authentication::LoginRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::authentication::LoginReply>>(AsyncLoginCheckRaw(context, request, cq));
    }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::authentication::LoginReply>* AsyncLoginCheckRaw(::grpc::ClientContext* context, const ::authentication::LoginRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub GRPC_FINAL : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::Channel>& channel);
    ::grpc::Status LoginCheck(::grpc::ClientContext* context, const ::authentication::LoginRequest& request, ::authentication::LoginReply* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::authentication::LoginReply>> AsyncLoginCheck(::grpc::ClientContext* context, const ::authentication::LoginRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::authentication::LoginReply>>(AsyncLoginCheckRaw(context, request, cq));
    }

   private:
    std::shared_ptr< ::grpc::Channel> channel_;
    ::grpc::ClientAsyncResponseReader< ::authentication::LoginReply>* AsyncLoginCheckRaw(::grpc::ClientContext* context, const ::authentication::LoginRequest& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    const ::grpc::RpcMethod rpcmethod_LoginCheck_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::Channel>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::SynchronousService {
   public:
    Service() : service_(nullptr) {}
    virtual ~Service();
    virtual ::grpc::Status LoginCheck(::grpc::ServerContext* context, const ::authentication::LoginRequest* request, ::authentication::LoginReply* response);
    ::grpc::RpcService* service() GRPC_OVERRIDE GRPC_FINAL;
   private:
    ::grpc::RpcService* service_;
  };
  class AsyncService GRPC_FINAL : public ::grpc::AsynchronousService {
   public:
    explicit AsyncService();
    ~AsyncService() {};
    void RequestLoginCheck(::grpc::ServerContext* context, ::authentication::LoginRequest* request, ::grpc::ServerAsyncResponseWriter< ::authentication::LoginReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag);
  };
};

}  // namespace authentication


#endif  // GRPC_authentication_5fservice_2eproto__INCLUDED