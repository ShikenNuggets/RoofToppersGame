#ifndef IGT_H
#define IGT_H

#include <Graphics/UI/TextUI.h>

namespace GamePackage{
	class IGT : public PizzaBox::TextUI{
	public:
		IGT(const std::string& name_, const PizzaBox::Rect& rect_, const std::string& fontName_);
		virtual ~IGT() override;

		virtual void Render() override;
	};
}

#endif //!IGT_H