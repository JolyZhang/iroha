/*
Copyright Soramitsu Co., Ltd. 2016 All Rights Reserved.

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

#include <infra/flatbuf/main_generated.h>

#include <memory>
#include <string>

namespace flatbuffer_autogen_extend {

inline flatbuffers::Offset<void> CreateCommand(flatbuffers::FlatBuffersBuilder &_fbb, const void *obj, Command type) {
  switch (type) {
    case Command_NONE: {
      return nullptr;
    }
    case Command_AssetCreate: {
      auto ptr = reinterpret_cast<const AssetCreate *>(obj);
      return ::iroha::CreateAssetCreateDirect(
        _fbb,
        ptr->asset_name()->c_str(),
        ptr->domain_name()->c_str(),
        ptr->ledger_name()->c_str(),
        ptr->creatorPubKey()->c_str()
      ).Union();
    }
    case Command_AssetAdd: {
      auto ptr = reinterpret_cast<const AssetAdd *>(obj);
      auto asset = std::vector<uint8_t>(
        ptr->asset()->begin(),
        ptr->asset()->end()
      );
      return ::iroha::CreateAssetAddDirect(
        _fbb,
        ptr->accPubKey()->c_str(),
        &asset
      ).Union();
    }
    case Command_AssetRemove: {
      auto ptr = reinterpret_cast<const AssetRemove *>(obj);
      auto asset = std::vector<uint8_t>(
        ptr->asset()->begin(),
        ptr->asset()->end()
      );
      return ::iroha::CreateAssetRemoveDirect(
        _fbb,
        ptr->accPubKey()->c_str(),
        &asset
      ).Union();
    }
    case Command_AssetTransfer: {
      auto ptr = reinterpret_cast<const AssetTransfer *>(obj);
      auto asset = std::vector<uint8_t>(
        ptr->asset()->begin(),
        ptr->asset()->end()
      );
      return ::iroha::CreateAssetTransferDirect(
        _fbb,
        &asset,
        ptr->sender()->c_str(),
        ptr->receiver()->c_str()
      ).Union();
    }
    case Command_PeerAdd: {
      auto ptr = reinterpret_cast<const PeerAdd *>(obj);
      auto peer = std::vector<uint8_t>(
        ptr->peer()->begin(),
        ptr->peer()->end()
      );
      return ::iroha::CreatePeerAddDirect(
        _fbb,
        &peer
      ).Union();
    }
    case Command_PeerRemove: {
      auto ptr = reinterpret_cast<const PeerRemove *>(obj);
      auto peer = std::vector<uint8_t>(
        ptr->peer()->begin(),
        ptr->peer()->end()
      );
      return ::iroha::CreatePeerRemoveDirect(
        _fbb,
        &peer
      ).Union();
    }
    case Command_PeerSetActive: {
      auto ptr = reinterpret_cast<const PeerSetActive *>(obj);
      return ::iroha::CreatePeerSetActiveDirect(
        _fbb,
        ptr->peerPubKey()->c_str(),
        ptr->active()
      ).Union();
    }
    case Command_PeerSetTrust: {
      auto ptr = reinterpret_cast<const PeerSetTrust *>(obj);
      return ::iroha::CreatePeerSetTrustDirect(
        _fbb,
        ptr->peerPubKey()->c_str(),
        ptr->trust()
      ).Union();
    }
    case Command_PeerChangeTrust: {
      auto ptr = reinterpret_cast<const PeerChangeTrust *>(obj);
      return ::iroha::CreatePeerChangeTrustDirect(
        _fbb,
        ptr->peerPubKey()->c_str(),
        ptr->delta()
      ).Union();
    }
    case Command_AccountAdd: {
      auto ptr = reinterpret_cast<const AccountAdd *>(obj);
      auto asset = std::vector<uint8_t>(
        ptr->account()->begin(),
        ptr->account()->end()
      );
      return ::iroha::CreateAccountAddDirect(
        _fbb,
        &asset,
      ).Union();
    }
    case Command_AccountRemove: {
      auto ptr = reinterpret_cast<const AccountRemove *>(obj);
      auto asset = std::vector<uint8_t>(
        ptr->account()->begin(),
        ptr->account()->end()
      );
      return ::iroha::CreateAccountRemoveDirect(
        _fbb,
        &asset,
      ).Union();
    }
    case Command_AccountAddSignatory: {
      auto ptr = reinterpret_cast<const AccountAddSignatory *>(obj);
      auto signatory = std::vector<flatbuffers::Offset<flatbuffers::String>>(
        ptr->signatory()->begin(),
        ptr->signatory()->end()
      );
      return ::iroha::CreateAccountAddSignatoryDirect(
        _fbb,
        ptr->account()->c_str(),
        &signatory
      ).Union();
    }
    case Command_AccountRemoveSignatory: {
      auto ptr = reinterpret_cast<const AccountRemoveSignatory *>(obj);
      return ::iroha::CreateAccountRemoveSignatoryDirect(
        _fbb,
        ptr->account()->c_str(),
        ptr->signatory()
      ).Union();
    }
    case Command_AccountSetUseKeys: {
      // TODO
      assert("Currently, doesn't support");
    }
    case Command_ChaincodeAdd: {
      // TODO
      assert("Currently, doesn't support");
    }
    case Command_ChaincodeRemove: {
      // TODO
      assert("Currently, doesn't support");
    }
    case Command_ChaincodeExecute: {
      // TODO
      assert("Currently, doesn't support");
    }
    default: return nullptr;
  }
}

}

namespace flatbuffer_service {

    std::string toString(const iroha::Transaction& tx){};

    /**
     * Encapsulate a transaction in a consensus event.
     */
    std::unique_ptr<ConsensusEvent> toConsensusEvent(const iroha::Transaction& fromTx) {
      
      
      flatbuffers::FlatBufferBuilder fbbConsensusEvent;

      // CreateSomething内でfbbのバッファにdeepコピーがされるならunique_ptrである必要はない。

      // At first, peerSignatures is empty. (Is this right?)
      auto peerSignatures = std::vector<flatbuffers::Offset<Signature>>();

      auto transactions = std::vector<flatbuffers::Offset<Transaction>>();

      auto signatures = std::vector<uint8_t>(
          fromTx->signatures()->begin(),
          fromTx->signatures()->end()
      );

      auto hashes = std::vector<uint8_t>(
          fromTx->hash()->begin(),
          fromTx->hash()->end()
      );

      auto data = std::vector<uint8_t>>(
          fromTx->attachment()->data()->begin(),
          fromTx->attachment()->data()->end()
      );
      
      auto attachmentOffset = ::iroha::CreateAttachmentDirect(
          fbb,
          fromTx->attachment()->mime()->c_str(),
          &data,
      );

      transactions->push_back(
          ::iroha::CreateTransactionDirect(
              fbbConsensusEvent,
              fromTx->creatorPubKey(),
              fromTx->command_type(),
              fromTx->command(),  // command()がconst void*でOffsetではないのはおかしい
              &signatures,
              &hashes,
              attachmentOffset
          ));
      }

      auto consensusEventOffset = ::iroha::CreateConsensusEventDirect(
          fbbConsensusEvent,
          &peerSignatures,
          &transactions
      );

      fbbConsensusEvent.Finish(consensusEventOffset);

      auto consensusEventFBPtr = fbbConsensusEvent.ReleaseBufferPointer();

      // Is it safe? Converting flatbuffers::unique_ptr_t to std::unique_ptr might lose valid deallocator.
      auto buf = consensusEventFBPtr.release();

      return flatbuffers::GetRoot<ConsensusEvent>(buf);
    }

    std::unique_ptr<iroha::ConsensusEvent> addSignature(const std::unique_ptr<iroha::ConsensusEvent>& event){}

};