#ifndef VALHALLA_ODIN_NARRATIVE_DICTIONARY_H_
#define VALHALLA_ODIN_NARRATIVE_DICTIONARY_H_

#include <vector>
#include <string>
#include <unordered_map>

#include <boost/property_tree/ptree.hpp>

namespace {

// Subset keys
constexpr auto kStartKey = "instructions.start";
constexpr auto kStartVerbalKey = "instructions.start_verbal";
constexpr auto kDestinationKey = "instructions.destination";
constexpr auto kDestinationVerbalAlertKey = "instructions.destination_verbal_alert";
constexpr auto kDestinationVerbalKey = "instructions.destination_verbal";
constexpr auto kContinueKey = "instructions.continue";
constexpr auto kContinueVerbalAlertKey = "instructions.continue_verbal_alert";
constexpr auto kContinueVerbalKey = "instructions.continue_verbal";
constexpr auto kBearKey = "instructions.bear";
constexpr auto kBearVerbalKey = "instructions.bear_verbal";
constexpr auto kPostTransitionVerbalKey = "instructions.post_transition_verbal";
constexpr auto kVerbalMultiCueKey = "instructions.verbal_multi_cue";

// Variable keys
constexpr auto kPhrasesKey = "phrases";
constexpr auto kCardinalDirectionsKey = "cardinal_directions";
constexpr auto kRelativeDirectionsKey = "relative_directions";
constexpr auto kEmptyStreetNameLabelsKey = "empty_street_name_labels";
constexpr auto kMetricLengthsKey = "metric_lengths";
constexpr auto kUsCustomaryLengthsKey = "us_customary_lengths";

// Empty street names label indexes
constexpr auto kWalkwayIndex = 0;
constexpr auto kCyclewayIndex = 1;
constexpr auto kMountainBikeTrailIndex = 2;

// Metric length indexes
constexpr auto kKilometersIndex = 0;
constexpr auto kOneKilometerIndex = 1;
constexpr auto kHalfKilometerIndex = 2;
constexpr auto kMetersIndex = 3;
constexpr auto kSmallMetersIndex = 4;

// US Customary length indexes
constexpr auto kMilesIndex = 0;
constexpr auto kOneMileIndex = 1;
constexpr auto kHalfMileIndex = 2;
constexpr auto kTenthsOfMileIndex = 3;
constexpr auto kOneTenthOfMileIndex = 4;
constexpr auto kFeetIndex = 5;
constexpr auto kSmallFeetIndex = 6;

// Phrase tags
constexpr auto kCardinalDirectionTag = "<CARDINAL_DIRECTION>";
constexpr auto kRelativeDirectionTag = "<RELATIVE_DIRECTION>";
constexpr auto kStreetNamesTag = "<STREET_NAMES>";
constexpr auto kBeginStreetNamesTag = "<BEGIN_STREET_NAMES>";
constexpr auto kLengthTag = "<LENGTH>";
constexpr auto kDestinationTag = "<DESTINATION>";
constexpr auto kCurrentVerbalCueTag = "<CURRENT_VERBAL_CUE>";
constexpr auto kNextVerbalCueTag = "<NEXT_VERBAL_CUE>";
constexpr auto kKilometersTag = "<KILOMETERS>";
constexpr auto kMetersTag = "<METERS>";
constexpr auto kMilesTag = "<MILES>";
constexpr auto kTenthsOfMilesTag = "<TENTHS_OF_MILE>";
constexpr auto kFeetTag = "<FEET>";

}

namespace valhalla {
namespace odin {

struct PhraseSet {
  std::unordered_map<std::string, std::string> phrases;
};

struct StartSubset : PhraseSet {
  std::vector<std::string> cardinal_directions;
  std::vector<std::string> empty_street_name_labels;
};

struct StartVerbalSubset : StartSubset {
  std::vector<std::string> metric_lengths;
  std::vector<std::string> us_customary_lengths;
};

struct DestinationSubset : PhraseSet {
  std::vector<std::string> relative_directions;
};

struct ContinueSubset : PhraseSet {
  std::vector<std::string> empty_street_name_labels;
};

struct ContinueVerbalSubset : ContinueSubset {
  std::vector<std::string> metric_lengths;
  std::vector<std::string> us_customary_lengths;
};

struct TurnSubset : PhraseSet {
  std::vector<std::string> relative_directions;
  std::vector<std::string> empty_street_name_labels;
};

struct PostTransitionVerbalSubset : PhraseSet {
  std::vector<std::string> metric_lengths;
  std::vector<std::string> us_customary_lengths;
  std::vector<std::string> empty_street_name_labels;
};

/**
 * A class that stores the localized narrative instructions.
 */
class NarrativeDictionary {
 public:
  NarrativeDictionary(const boost::property_tree::ptree& narrative_pt);

  // Start
  StartSubset start_subset;
  StartVerbalSubset start_verbal_subset;

  // Destination
  DestinationSubset destination_subset;
  DestinationSubset destination_verbal_alert_subset;
  DestinationSubset destination_verbal_subset;

  // Continue
  ContinueSubset continue_subset;
  ContinueSubset continue_verbal_alert_subset;
  ContinueVerbalSubset continue_verbal_subset;

  // Bear
  TurnSubset bear_subset;
  TurnSubset bear_verbal_subset;

  // Post transition verbal
  PostTransitionVerbalSubset post_transition_verbal_subset;

  // Verbal miulti-cue
  PhraseSet verbal_multi_cue_subset;

 protected:

  /**
    * Loads this dictionary object with the localized narrative instructions
    * contained in the specified property tree.
    *
    * @param  narrative_pt  The narrative property tree with the localized
    *                       narrative instructions.
    */
  void Load(const boost::property_tree::ptree& narrative_pt);

  /**
    * Loads the phrases with the localized narrative instructions
    * contained in the specified property tree.
    *
    * @param  phrase_handle  The 'phrase' structure to populate.
    * @param  phrase_pt  The 'phrase' property tree.
    */
  void Load(PhraseSet& phrase_handle, const boost::property_tree::ptree& phrase_pt);

  /**
    * Loads the specified 'start' instruction subset with the localized narrative
    * instructions contained in the specified property tree.
    *
    * @param  start_handle  The 'start' structure to populate.
    * @param  start_subset_pt  The 'start' property tree.
    */
  void Load(StartSubset& start_handle,
            const boost::property_tree::ptree& start_subset_pt);
  /**
    * Loads the specified 'start verbal' instruction subset with the localized
    * narrative instructions contained in the specified property tree.
    *
    * @param  start_verbal_handle  The 'start verbal' structure to populate.
    * @param  start_verbal_subset_pt  The 'start verbal' property tree.
    */
  void Load(StartVerbalSubset& start_verbal_handle,
            const boost::property_tree::ptree& start_verbal_subset_pt);

  /**
    * Loads the specified 'destination' instruction subset with the localized
    * narrative instructions contained in the specified property tree.
    *
    * @param  destination_handle  The 'destination' structure to populate.
    * @param  destination_subset_pt  The 'destination' property tree.
    */
  void Load(DestinationSubset& destination_handle,
            const boost::property_tree::ptree& destination_subset_pt);

  /**
    * Loads the specified 'continue' instruction subset with the localized
    * narrative instructions contained in the specified property tree.
    *
    * @param  continue_handle  The 'continue' structure to populate.
    * @param  continue_subset_pt  The 'continue' property tree.
    */
  void Load(ContinueSubset& continue_handle,
            const boost::property_tree::ptree& continue_subset_pt);

  /**
    * Loads the specified 'continue verbal' instruction subset with the localized
    * narrative instructions contained in the specified property tree.
    *
    * @param  continue_verbal_handle  The 'continue verbal' structure to populate.
    * @param  continue_verbal_subset_pt  The 'continue verbal' property tree.
    */
  void Load(ContinueVerbalSubset& continue_verbal_handle,
            const boost::property_tree::ptree& continue_verbal_subset_pt);

  /**
    * Loads the specified 'turn' instruction subset with the localized
    * narrative instructions contained in the specified property tree.
    *
    * @param  turn_handle  The 'turn' structure to populate.
    * @param  turn_subset_pt  The 'turn' property tree.
    */
  void Load(TurnSubset& turn_handle,
            const boost::property_tree::ptree& turn_subset_pt);

  /**
    * Loads the specified 'post transition verbal' instruction subset with the
    * localized narrative instructions contained in the specified property tree.
    *
    * @param  post_transition_verbal_handle  The 'post transition verbal'
    *                                        structure to populate.
    * @param  post_transition_verbal_subset_pt  The 'post transition verbal'
    *                                           property tree.
    */
  void Load(PostTransitionVerbalSubset& post_transition_verbal_handle,
            const boost::property_tree::ptree& post_transition_verbal_subset_pt);

};

}
}

#endif  // VALHALLA_ODIN_NARRATIVE_DICTIONARY_H_