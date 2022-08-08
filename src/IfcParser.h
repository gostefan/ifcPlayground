
#include <istream>
#include <memory>
#include <string>
#include <unordered_map>

namespace ifc::in {

class IfcParser {
	public:
	IfcParser(std::wistream& sourceData);
	~IfcParser();

	std::unordered_map<size_t, std::wstring> const& getContents() const;

	private:
	struct Pimpl;
	std::unique_ptr<Pimpl> pimpl;
};

} // namespace ifc::in
