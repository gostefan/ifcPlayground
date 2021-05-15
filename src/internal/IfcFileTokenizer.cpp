
#include "IfcFileTokenizer.h"

#include <list>


namespace ifc::in {

namespace {

class FileColonToken : public IfcToken {
  public:
	virtual ~FileColonToken() = default;

	std::pair<size_t, size_t> getLineAndPos(size_t contentPos) const override {
		return { startLine, startOffset + contentPos };
	}

	std::pair<size_t, size_t> getEndLineAndPos() { return { 0u, getValue().size() }; }

	static std::unique_ptr<IfcToken> makeUnique(
			std::wstring&& content, size_t startLine, size_t startOffset) {
		return std::unique_ptr<IfcToken>(
				new FileColonToken(std::move(content), startLine, startOffset));
	}

  private:
	FileColonToken(std::wstring&& noNewlineContent, size_t startLine, size_t startOffset) :
		IfcToken(std::move(noNewlineContent)), startLine(startLine), startOffset(startOffset) {}

	size_t startLine;
	size_t startOffset;
};

} // anonymous namespace

void IfcFileTokenizer::moveToNextToken() {
	currentToken.reset();

	auto const tokenStartPos = currentPos;
	std::wstring nextTokenContent;
	std::getline(stream, nextTokenContent, L';');

	if (!stream) // Handle EoF
		return;
	
	currentPos += nextTokenContent.size() + 1; // Don't forget the removed colon

	// Todo: Remove Comments & newlines in reasonable fashion

	currentToken = FileColonToken::makeUnique(std::move(nextTokenContent), 0, tokenStartPos);
};

std::shared_ptr<IfcToken> const&
IfcFileTokenizer::getCurrentToken() const { // TODO: Should not return by value
	return currentToken;
}

} // namespace ifc::in
