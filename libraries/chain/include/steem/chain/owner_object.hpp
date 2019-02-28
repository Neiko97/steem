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

   class plan_object : public object< plan_object_type, plan_object >
   {
      plan_object() = delete;

      public:
         template< typename Constructor, typename Allocator >
         plan_object( Constructor&& c, allocator< Allocator > a )
         {
            c( *this );
         }

         plan_id_type      id;
         account_name_type owner;
         plan_name_type    name;
         asset             cost = asset( 0, SBD_SYMBOL );
         uint64_t          period; // in seconds
         uint32_t          number_documents = 0;
         time_point_sec    last_update;
   };

   class plan_item_object : public object< plan_item_object_type, plan_item_object >
   {
      plan_item_object() = delete;

      public:
         template< typename Constructor, typename Allocator >
         plan_item_object( Constructor&& c, allocator< Allocator > a )
         {
            c( *this );
         }

         plan_item_id_type       id;
         plan_item_id_item_type  id_item;
         account_name_type       owner;
         plan_name_type          name;
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

   struct by_owner_name;
   typedef multi_index_container<
      plan_object,
      indexed_by<
         ordered_unique< tag< by_id >, member< plan_object, plan_id_type, &plan_object::id > >,
         ordered_unique< tag< by_owner_name >,
            composite_key< plan_object,
               member< plan_object, account_name_type, &plan_object::owner >,
               member< plan_object, plan_name_type, &plan_object::name >
            >,
            composite_key_compare< std::less< account_name_type >, std::less< plan_name_type > >
         >
      >,
      allocator< plan_object >
   > plan_index;

   struct by_id_item;
   typedef multi_index_container<
      plan_item_object,
      indexed_by<
         ordered_unique< tag< by_id >, member< plan_item_object, plan_item_id_type, &plan_item_object::id > >,
         ordered_non_unique< tag< by_owner_name >,
            composite_key< plan_item_object,
               member< plan_item_object, account_name_type, &plan_item_object::owner >,
               member< plan_item_object, plan_name_type, &plan_item_object::name >
            >,
            composite_key_compare< std::less< account_name_type >, std::less< plan_name_type > >
         >,
         ordered_non_unique< tag< by_id_item >,
            composite_key< plan_item_object,
               member< plan_item_object, plan_item_id_item_type, &plan_item_object::id_item >,
               member< plan_item_object, account_name_type, &plan_item_object::owner >,
               member< plan_item_object, plan_name_type, &plan_item_object::name >
            >
         >
      >,
      allocator< plan_item_object >
   > plan_item_index;
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

FC_REFLECT( steem::chain::plan_object,
             (id)
             (owner)
             (name)
             (cost)
             (period)
             (number_documents)
             (last_update)
          )
CHAINBASE_SET_INDEX_TYPE( steem::chain::plan_object, steem::chain::plan_index )

FC_REFLECT( steem::chain::plan_item_object,
             (id)
             (id_item)
             (owner)
             (name)
          )
CHAINBASE_SET_INDEX_TYPE( steem::chain::plan_item_object, steem::chain::plan_item_index )
