
#pragma once

#include "IfcToken.h"

#include <istream>
#include <memory>


namespace ifc::in {

class IfcFileTokenizer {
  public:
	IfcFileTokenizer(std::wistream& sourceData) : stream(sourceData) { moveToNextToken(); }
	IfcFileTokenizer(const IfcFileTokenizer& other) = delete;
	IfcFileTokenizer& operator=(const IfcFileTokenizer& other) = delete;

	std::shared_ptr<IfcToken> const& getCurrentToken() const;
	void moveToNextToken();

  private:
	std::wistream& stream;

	size_t currentLine = 0;
	size_t currentPos = 0;

	std::shared_ptr<IfcToken> currentToken;
};

} // namespace ifc::in