
#include "IfcFileTokenizer.h"

#include <list>
#include <tuple>
#include <vector>


namespace ifc::in {

namespace {

using RemovedCharacters = std::tuple<uint64_t, uint64_t, uint64_t>; // position, character count,
																	// newline count

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

void insertRemoval(uint64_t removalPos, uint64_t removedChars, uint64_t removedNewlines,
		std::vector<RemovedCharacters>& removals) {
	uint64_t removedCharCount = 0;
	for (auto iter = removals.begin(), end = removals.end(); iter != end; iter++) {
		if (std::get<0>(*iter) <= removalPos + )
			removedCharCount += 
	}
}

void removeNewlines(std::wstring& content, std::vector<RemovedCharacters>& removedCharacters) {
	for (auto newlinePos = content.find_first_of(L"\n\r"); newlinePos != std::wstring::npos;
			newlinePos = content.find_first_of(L"\n\r")) {
		uint64_t removedNewlines = 1;

		// Handle all newline combinations
		if (content.size() >= newlinePos &&
				((content[newlinePos] == L'\n' && content[newlinePos + 1] == L'\r') ||
						(content[newlinePos] == L'\r' && content[newlinePos + 1] == L'\n')))
			removedNewlines++;

		insertRemoval(newlinePos, removedNewlines, 1, removedCharacters);
		content.erase(newlinePos, removedNewlines);
	}
}

} // anonymous namespace

void IfcFileTokenizer::moveToNextToken() {
	currentToken.reset();

	auto const tokenStartPos = currentPos;
	std::wstring nextTokenContent;
	std::getline(stream, nextTokenContent, L';');

	if (!stream) // Handle EoF
		return;

	currentPos += nextTokenContent.size() + 1; // Don't forget the removed colon

	std::vector<RemovedCharacters> removedCharacters;
	removeNewlines(nextTokenContent, removedCharacters);
	// Todo: Remove Comments & newlines in reasonable fashion

	currentToken = FileColonToken::makeUnique(std::move(nextTokenContent), 0, tokenStartPos);
};

std::shared_ptr<IfcToken> const&
IfcFileTokenizer::getCurrentToken() const { // TODO: Should not return by value
	return currentToken;
}

} // namespace ifc::in
