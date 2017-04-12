/*
Copyright Soramitsu Co., Ltd. 2016 All Rights Reserved.
http://soramitsu.co.jp

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

                 http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef __CONNECTION__
#define __CONNECTION__

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include <infra/flatbuf/endpoint.grpc.fb.h>
#include <infra/flatbuf/main_generated.h>

namespace connection {

using iroha::ConsensusEvent;
using iroha::Transaction;

struct Config {
  std::string name;
  std::string ip_addr;
  std::string port;
};

namespace iroha { namespace SumeragiImpl { namespace Verify {

using CallBackFunc =
    std::function<void(const std::string & /* from */,
                       std::unique_ptr<ConsensusEvent> /* message */)>;

bool send(const std::string &ip, const std::unique_ptr<ConsensusEvent>& msg);
bool sendAll(const std::unique_ptr<ConsensusEvent>& msg);
void receive(Verify::CallBackFunc &&callback);

}}}  // namespace iroha::SumeragiImpl::Verify

namespace iroha { namespace SumeragiImpl { namespace Torii {


using CallBackFunc = std::function<void(
    const std::string & /* from */,
    std::unique_ptr<Transaction> /* message */)>;

void receive(Torii::CallBackFunc &&callback);

}}}  // namespace iroha::SumeragiImpl::Verify

void initialize_peer();
int run();
void finish();

}  // namespace connection

#endif
