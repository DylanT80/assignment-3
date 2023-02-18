#include "movie_action.h"

int MovieAction::calculate_late_fees(int num_of_days_past_due) {
    // Determine if mercy
    bool has_mercy = get_inventory_id() % 13 == 0 && action_movie_mercy_rule_apply();
    // Mercy rule applies, fee is 0
    if (has_mercy)
        return 0;
    else
    {
        // Days greater than 5
        if (num_of_days_past_due >= 5)
            return 2*(num_of_days_past_due * late_fee_per_day_in_dollar);
        return num_of_days_past_due * late_fee_per_day_in_dollar;
    }
}

bool MovieAction::action_movie_mercy_rule_apply() {
    return title.find("pulp fiction") != std::string::npos;
}

bool MovieAction::mercy_rule_apply() {
    return StoreMediaInterface::mercy_rule_apply() && action_movie_mercy_rule_apply();
}