#pragma once
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>

#include <graphene/db2/database.hpp>

#include <steemit/protocol/types.hpp>
#include <steemit/protocol/authority.hpp>


namespace steemit { namespace chain {

namespace bip = graphene::db2::bip;
using namespace boost::multi_index;

using boost::multi_index_container;

using graphene::db2::object;
using graphene::db2::oid;
using graphene::db2::allocator;

using steemit::protocol::block_id_type;
using steemit::protocol::transaction_id_type;
using steemit::protocol::chain_id_type;
using steemit::protocol::account_name_type;
using steemit::protocol::share_type;
using steemit::protocol::shared_authority;

typedef bip::basic_string< char, std::char_traits< char >, allocator< char > > shared_string;
inline std::string to_string( const shared_string& str ) { return std::string( str.begin(), str.end() ); }
inline void from_string( shared_string& out, const string& in ){ out.assign( in.begin(), in.end() ); }

struct by_id;

enum object_type
{
   dynamic_global_property_object_type,
   account_object_type,
   witness_object_type,
   transaction_object_type,
   block_summary_object_type,
   witness_schedule_object_type,
   comment_object_type,
   comment_vote_object_type,
   witness_vote_object_type,
   limit_order_object_type,
   feed_history_object_type,
   convert_request_object_type,
   liquidity_reward_balance_object_type,
   operation_object_type,
   account_history_object_type,
   category_object_type,
   hardfork_property_object_type,
   withdraw_vesting_route_object_type,
   owner_authority_history_object_type,
   account_recovery_request_object_type,
   change_recovery_account_request_object_type,
   escrow_object_type,
   savings_withdraw_object_type,
   decline_voting_rights_request_object_type
};

class dynamic_global_property_object;
class account_object;
class witness_object;
class transaction_object;
class block_summary_object;
class witness_schedule_object;
class comment_object;
class comment_vote_object;
class witness_vote_object;
class limit_order_object;
class feed_history_object;
class convert_request_object;
class liquidity_reward_balance_object;
class operation_object;
class account_history_object;
class category_object;
class hardfork_property_object;
class withdraw_vesting_route_object;
class owner_authority_history_object;
class account_recovery_request_object;
class change_recovery_account_request_object;
class escrow_object;
class savings_withdraw_object;
class decline_voting_rights_request_object;

typedef oid< dynamic_global_property_object         > dynamic_global_property_id_type;
typedef oid< account_object                         > account_id_type;
typedef oid< witness_object                         > witness_id_type;
typedef oid< transaction_object                     > transaction_object_id_type;
typedef oid< block_summary_object                   > block_summary_id_type;
typedef oid< witness_schedule_object                > witness_schedule_id_type;
typedef oid< comment_object                         > comment_id_type;
typedef oid< comment_vote_object                    > comment_vote_id_type;
typedef oid< witness_vote_object                    > witness_vote_id_type;
typedef oid< limit_order_object                     > limit_order_id_type;
typedef oid< feed_history_object                    > feed_history_id_type;
typedef oid< convert_request_object                 > convert_request_id_type;
typedef oid< liquidity_reward_balance_object        > liquidity_reward_balance_id_type;
typedef oid< operation_object                       > operation_id_type;
typedef oid< account_history_object                 > account_history_id_type;
typedef oid< category_object                        > category_id_type;
typedef oid< hardfork_property_object               > hardfork_property_id_type;
typedef oid< withdraw_vesting_route_object          > withdraw_vesting_route_id_type;
typedef oid< owner_authority_history_object         > owner_authority_history_id_type;
typedef oid< account_recovery_request_object        > account_recovery_request_id_type;
typedef oid< change_recovery_account_request_object > change_recovery_account_request_id_type;
typedef oid< escrow_object                          > escrow_id_type;
typedef oid< savings_withdraw_object                > savings_withdraw_id_type;
typedef oid< decline_voting_rights_request_object   > decline_voting_rights_request_id_type;

} } //steemit::chain

namespace fc
{
   class variant;
   void to_variant( const steemit::chain::shared_string& s, variant& var )
   {
      var = fc::string( steemit::chain::to_string( s ) );
   }

   void from_variant( const variant& var, steemit::chain::shared_string& s )
   {
      auto str = var.as_string();
      s.assign( str.begin(), str.end() );
   }
}

FC_REFLECT_ENUM( steemit::chain::object_type,
                 (dynamic_global_property_object_type)
                 (account_object_type)
                 (witness_object_type)
                 (transaction_object_type)
                 (block_summary_object_type)
                 (witness_schedule_object_type)
                 (comment_object_type)
                 (category_object_type)
                 (comment_vote_object_type)
                 (witness_vote_object_type)
                 (limit_order_object_type)
                 (feed_history_object_type)
                 (convert_request_object_type)
                 (liquidity_reward_balance_object_type)
                 (operation_object_type)
                 (account_history_object_type)
                 (hardfork_property_object_type)
                 (withdraw_vesting_route_object_type)
                 (owner_authority_history_object_type)
                 (account_recovery_request_object_type)
                 (change_recovery_account_request_object_type)
                 (escrow_object_type)
                 (savings_withdraw_object_type)
                 (decline_voting_rights_request_object_type)
               )

FC_REFLECT_TYPENAME( steemit::chain::shared_string )
