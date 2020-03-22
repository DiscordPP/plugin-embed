#pragma once

#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>

#include <nlohmann/json.hpp>

namespace discordpp {

  /**
   * @class MessageEmbed
   * @details Anything denoted as "optional" can have a nullptr as input
   */

  class MessageEmbed {
  public:

    /**
     * @param title
     * @details Sets embed title.
     * @returns MessageEmbed
     */

    MessageEmbed setTitle(std::string title){
      embed["title"] = title;

      return *this;
    };

    /**
     * @param desc
     * @details Sets embed description
     * @returns MessageEmbed
     */

    MessageEmbed setDescription(std::string desc) {
      embed["description"] = desc;

      return *this;
    };

    /**
     * @param color
     * @details Sets embed color
     * @returns MessageEmbed
     */

    MessageEmbed setColor(int color){
      embed["color"] = color;

      return *this;
    };

    /**
     * @param url
     * @details Sets embed url for title
     * @returns MessageEmbed
     */

    MessageEmbed setURL(std::string url) {
      embed["url"] = url;

      return *this;
    };

    /**
     * @param footText
     * @details Sets footer text for embed
     * @returns MessageEmbed
     */

    MessageEmbed setFooterText (std::string footText) {
      embed["footer"]["text"] = footText;

      return *this;
    };

    /**
     * @param footIconURL
     * @details Sets footer icon for embed
     * @returns MessageEmbed
     */

    MessageEmbed setFooterIconURL (std::string footIconURL){
      embed["footer"]["icon_url"] = footIconURL;

      return *this;
    };

    /**
     * @param title
     * @param desc
     * @param _inline
     * @details Adds new fields to embed. desc is optional.
     * @returns MessageEmbed
     */

    MessageEmbed addField (std::string title, std::string desc, bool _inline){
      if (embed.find("fields") == embed.end()) embed["fields"] = nlohmann::json::array();

      nlohmann::json toPush;

      toPush["name"] = title;
      toPush["value"] = desc;
      toPush["inline"] = _inline;

      embed["fields"].push_back(toPush);

      return *this;
    };

    /**
     * @param url
     * @details Sets image url for embed. Not compatible with MessageEmbed#setThumbnail
     * @returns MessageEmbed
     */

    MessageEmbed setImage (std::string url) {
      embed["image"]["url"] = url;

      return *this;
    };

    /**
     * @param url
     * @details Sets thumbnail url for embed. Not compatible with MessageEmbed#setImage
     * @returns MessageEmbed
     */

    MessageEmbed setThumbnail (std::string url) {
      embed["thumbnail"]["url"] = url;

      return *this;
    };

    /**
     * @param name
     * @param iconURL
     * @details Sets author name and icon. iconURL is optional.
     * @returns MessageEmbed
     */

    MessageEmbed setAuthor(std::string name, std::string iconURL) {
      embed["author"]["name"] = name;
      embed["author"]["icon_url"] = iconURL;

      return *this;
    };

    /**
     * @param timestamp
     * @details Sets ISO 8061 Timestamp. timestamp is optional and will default to now.
     * @returns MessageEmbed
     */

    MessageEmbed setTimestamp(std::string timestamp) {
      if (!timestamp.empty()) {
        embed["timestamp"] = timestamp;
      } else {
        time_t now;
        time(&now);
        char buf[sizeof "2011-10-08T07:07:09Z"];
        strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));
        embed["timestamp"] = (std::string)buf;
      }

      return *this;
    };

    MessageEmbed setTimestamp2(std::string timestamp) {
      if (!timestamp.empty()) {
        embed["timestamp"] = timestamp;
      } else {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);

        std::string out(21, '0');
        char* buf = &out[0];

        std::strftime(buf, 21, "%FT%TZ", gmtime(&now_time));

        std::cout << out << std::endl;

        embed["timestamp"] = out;

        std::cout << embed["timestamp"].get<std::string>() << std::endl;
      }

      return *this;
    }

    /**
     * @returns JSON
     */

    nlohmann::json getEmbed(){
      return embed;
    }
  protected:

    /**
     * @name embed
     * @protected
     * @details MessageEmbed JSON storage.
     */

    nlohmann::json embed;
  };
}
