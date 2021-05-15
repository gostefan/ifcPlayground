
#pragma once

#include <string>
#include <utility>


namespace ifc::in {

class IfcToken {
  public:
	virtual ~IfcToken() = default;

	virtual std::pair<size_t, size_t> getLineAndPos(size_t tokenPos) const = 0;
	virtual std::wstring_view const getValue() const { return value; }

  protected:
	IfcToken(std::wstring&& token) : value(token){};

  private:
	std::wstring value;
};

} // namespace ifc::in
