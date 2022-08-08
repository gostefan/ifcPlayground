#include "IfcParser.h"

#include <algorithm>
#include <string>
#include <utility>

#include "IfcFileColonTokenizer.h"
#include "IfcToken.h"

#include <iostream>


namespace ifc::in {

namespace {

class NumberedToken : public IfcToken {
  public:
	NumberedToken(std::wstring const& token, size_t startLine, size_t startPos) : 
			IfcToken(token), line(startLine), pos(startPos) {}
	NumberedToken(std::wstring&& token, size_t startLine, size_t startPos) : 
			IfcToken(std::move(token)), line(startLine), pos(startPos) {}
	std::pair<size_t, size_t> getLineAndPos(size_t tokenPos) const {
		// TODO: Implement
	}
  private:
	std::wstring&& removeNewlines(std::wstring const& token) {
		std::wstring_view restToken(token);
		std::wstring result;

		while (restToken.size() > 0)
			restToken = processNextNewline(restToken, result);
	}

	std::wstring_view processNextNewline(std::wstring_view const& view, std::wstring& result) {
		size_t const nextPos = view.find_first_of(L"\n\r");
		result.append(view.begin(), view.begin() + nextPos);

		if (nextPos == view.npos)
			return std::wstring_view{};

		if (nextPos == 0 && newlinePos.back().second.size() == 1 && newlinePos.back().second[0] != view[0])
			newlinePos.back().second.append(view.begin(), view.begin() + 1);
		else {
			auto const lastPos = !newlinePos.empty() ? newlinePos.back().first : 0;
			newlinePos.emplace_back(lastPos + nextPos, std::wstring{view[nextPos]});
		}

		return view.substr(nextPos + 1);
	}

	std::vector<std::pair<size_t, std::wstring>> newlinePos;
	size_t line, pos;
};

std::string toPosString(std::pair<size_t, size_t> const& pos) { return " on line " + std::to_string(pos.first) + " at pos " + std::to_string(pos.second); }

} // anonymous namespace

struct IfcParser::Pimpl {
	Pimpl(std::wistream& sourceData) {
		if (!sourceData)
			throw std::runtime_error("Invalid stream passed to IfcParser ctor.");

		IfcFileColonTokenizer wrappedData(sourceData);
		for (std::shared_ptr<IfcToken> token : wrappedData) {
			parseHeader(*token);
			parseContent(*token);
		}

	}

	void parseHeader(IfcToken const& colonToken) {
		// TODO: Implement
	}

	void parseContent(IfcToken const& token) {
		std::wstring const& content = token.getValue();
		if (content.size() > 0) {
			auto hashTag = content.find('#');
			if (hashTag == content.npos)
				throw std::runtime_error("No hash character found on line " + std::to_string(token.getLineAndPos(0).first));

			auto pos = content.find('=', hashTag);
			if (pos == content.npos)
				throw std::runtime_error("No assignment character found on line " + std::to_string(token.getLineAndPos(0).first));

			size_t id = std::stoull(content.substr(hashTag + 1, pos-hashTag-1));
			auto const value = content.substr(pos + 1);
			if (contents.count(id) > 0)
				throw std::runtime_error("Duplicate ids are illegal. Second definition on line " + std::to_string(token.getLineAndPos(hashTag + 1).first));
			contents.emplace(id, value);
		}
	}

	std::unordered_map<size_t, std::wstring> contents;
};

IfcParser::IfcParser(std::wistream& sourceData) : pimpl(std::make_unique<Pimpl>(sourceData)) {}

IfcParser::~IfcParser() = default;

std::unordered_map<size_t, std::wstring> const& IfcParser::getContents() const {
	return pimpl->contents;
}

} // namespace ifc::in
