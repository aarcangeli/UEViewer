#include "BaseDialog.h"
#include "../../UmodelTool/res/resource.h"

class TestDialog : public UIBaseDialog
{
public:
	void Show()
	{
		value1 = false;
		value2 = true;
		value3 = 0;
		ShowModal("UI Test", 350, 200);
		printf("v1=%d v2=%d v3=%d\n", value1, value2, value3);
	}

	virtual void InitUI()
	{
		UIMenu* menu = new UIMenu;
		SetMenu(menu);

		(*menu)
		[
			NewSubmenu("Menu")
			[
				NewMenuItem("First item\tCtrl+T")
				+ NewMenuSeparator()
				+ NewMenuCheckbox("Item #1", &value1)
					.Expose(item1)
				+ NewMenuCheckbox("Item #2", &value2)
				+ NewMenuSeparator()
				+ NewMenuRadioGroup(&value3)
				[
					NewMenuRadioButton("Value 0", 0)
					+ NewMenuRadioButton("Value 1", 1)
					+ NewMenuRadioButton("Value 2", 2)
				]
				+ NewMenuSeparator()
				+ NewMenuItem("Last Item")
			]
		];

		(*this)
		[
			NewControl(UIGroup, GROUP_NO_BORDER|GROUP_HORIZONTAL_LAYOUT)
			[
				NewControl(UIGroup, GROUP_NO_BORDER)
				.SetWidth(70)
				[
					NewControl(UIHyperLink, "Test link", "http://www.gildor.org/")
					+ NewControl(UIBitmap)
						.SetWidth(64)
						.SetHeight(64)
						.SetResourceIcon(IDC_MAIN_ICON)
					+ NewControl(UIBitmap)
						.SetX(16)
						.SetWidth(32)
						.SetHeight(32)
						.SetResourceIcon(IDC_MAIN_ICON)
					+ NewControl(UIBitmap)
						.SetX(24)
						.SetWidth(16)
						.SetHeight(16)
						.SetResourceIcon(IDC_MAIN_ICON)
				]
				+ NewControl(UISpacer, 8)
				+ NewControl(UIVerticalLine)
				.SetHeight(100)
				+ NewControl(UISpacer, 8)
				+ NewControl(UIGroup, GROUP_NO_BORDER)
				[
					NewControl(UIGroup, GROUP_NO_BORDER|GROUP_HORIZONTAL_LAYOUT)
					[
						NewControl(UIGroup, "Menu control")
						[
							NewControl(UICheckbox, "Enable item #1", true)
							.SetCallback(BIND_MEM_CB(&TestDialog::OnEnableItem1, this))
							+ NewControl(UICheckbox, "Item #1", &value1)
							+ NewControl(UICheckbox, "Item #2", &value2)
						]
						+ NewControl(UISpacer)
						+ NewControl(UIGroup, "Group 1")
						[
							NewControl(UIButton, "Button 1")
							+ NewControl(UIButton, "Button 2")
						]
						+ NewControl(UISpacer)
						+ NewControl(UIGroup, "Group 2")
						.SetRadioVariable(&value3)
						[
							NewControl(UIRadioButton, "Value 0", 0)
							+ NewControl(UIRadioButton, "Value 1", 1)
							+ NewControl(UIRadioButton, "Value 2", 2)
						]
					]
					+ NewControl(UISpacer, 8)
					+ NewControl(UIHorizontalLine)
					+ NewControl(UISpacer, 8)
					+ NewControl(UIGroup, GROUP_NO_BORDER|GROUP_HORIZONTAL_LAYOUT)
					[
						NewControl(UISpacer, -1)
						+ NewControl(UIButton, "Close")
						.SetWidth(100)
						.SetOK()
					]
				]
			]
		];
	}

	void OnEnableItem1(UICheckbox* sender, bool value)
	{
		item1->Enable(value);
	}

	UIMenuItem*		item1;
	bool			value1;
	bool			value2;
	int				value3;
};

void main()
{
	TestDialog dialog;
	dialog.Show();
}
