#include <eosio.system/eosio.system.hpp>

namespace eosiosystem {

   void system_contract::setprioacts( const std::vector<priority_action>& actions ) {
      require_auth( get_self() );

      check( actions.size() <= max_priority_actions, "too many priority actions" );
      for( size_t i = 0; i < actions.size(); ++i ) {
         const auto& a = actions[i];
         check( is_account( a.contract ), "priority action contract does not exist: " + a.contract.to_string() );
         check( a.action != name(), "priority action name is empty" );
         check( i == 0 || actions[i - 1] < a, "priority actions must be sorted by (contract, action) without duplicates" );
      }

      priority_actions_singleton prio( get_self(), get_self().value );
      if( actions.empty() ) {
         prio.remove();
      } else {
         prio.set( priority_actions{ actions }, get_self() );
      }
   }

} /// namespace eosiosystem
