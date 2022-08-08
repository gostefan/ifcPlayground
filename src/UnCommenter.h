
include "IfcToken.h"

namespace ifc::in {

class UnCommenter {
	public:
	UnCommenter(std::wistream& sourceData);
	~IfcParser();

	std::unordered_map<size_t, std::wstring> const& getContents() const;

	private:
	struct Pimpl;
	std::unique_ptr<Pimpl> pimpl;
};

} // namespace ifc::in
