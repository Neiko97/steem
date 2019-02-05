#pragma once

#include <steem/protocol/authority.hpp>
#include <steem/protocol/steem_operations.hpp>

#include <steem/chain/steem_object_types.hpp>

#include <boost/multi_index/composite_key.hpp>

namespace steem { namespace chain {

   using steem::protocol::public_key_type;
   using steem::protocol::asset;
   using steem::protocol::asset_symbol_type;
   
   /**
    *  Owner is a new type of account that stablishes a
    *  hierarchical governance inside the blockchain, for
    *  the purposes of the European Commision    
    */
   class owner_object : public object< owner_object_type, owner_object >
   {
      owner_object() = delete;

      public:
         enum owner_role_type
         {
            none
         };

         template< typename Constructor, typename Allocator >
         owner_object( Constructor&& c, allocator< Allocator > a )            
         {
            c( *this );
         }

         id_type           id;

         account_name_type owner;
         time_point_sec    created;
         account_name_type creator;
         
         public_key_type   signing_key;
         owner_role_type   role = none;
         
         asset             backed_sbd = asset( 0, SBD_SYMBOL );         
   };
   
   struct by_backed_sbd;
   /**
    * @ingroup object_index
    */
   typedef multi_index_container<
      owner_object,
      indexed_by<
         ordered_unique< tag< by_id >, member< owner_object, owner_id_type, &owner_object::id > >,
         ordered_unique< tag< by_name >, member< owner_object, account_name_type, &owner_object::owner > >
      >,
      allocator< owner_object >
   > owner_index;   

} }

FC_REFLECT_ENUM( steem::chain::owner_object::owner_role_type, (none) )

FC_REFLECT( steem::chain::owner_object,
             (id)
             (owner)
             (created)
             (creator)
             (signing_key)
             (role)
             (backed_sbd)
          )
CHAINBASE_SET_INDEX_TYPE( steem::chain::owner_object, steem::chain::owner_index )
