/***************************************************************
 * Name:      Create_Passwords_gui_1_0Main.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2019-10-13
 * Copyright:  ()
 * License:
 **************************************************************/

#include "Create_Passwords_gui_1_0Main.h"
#include <wx/msgdlg.h>
#include <iostream>
#include <fstream>
#include <wx/log.h>
#include <wx/string.h>
#include <time.h>
#include <string>
#include <wx/valnum.h>
#include <wx/valtext.h>
#include <wx/msgdlg.h>




#define CH 256

using namespace std;

//after all ok
int OnlySymbols();
int OnlyUppercase();
int OnlyLowercase();
int OnlyNumbers();


string OnlyMiningWords();

void FileTestIfExist();
void FileTestSize();
void PasswordSaveToText();


string RandomAddCharsToStr(string tmp,int len); ///random add charcters to string  e.g.. ## or aa or AA or 88


//(*InternalHeaders(Create_Passwords_gui_1_0Frame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(Create_Passwords_gui_1_0Frame)
const long Create_Passwords_gui_1_0Frame::ID_BUTTON1 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_RICHTEXTCTRL1 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_STATICTEXT2 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_STATICTEXT3 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_TEXTCTRL1 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_STATICTEXT4 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_TEXTCTRL2 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_RADIOBUTTON1 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_RADIOBUTTON2 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_STATICTEXT7 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_RADIOBUTTON3 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_CHECKBOX1 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_CHECKBOX2 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_CHECKBOX3 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_CHECKBOX4 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_CONTEXTHELPBUTTON1 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_TEXTCTRL3 = wxNewId();
const long Create_Passwords_gui_1_0Frame::WhereInPass1 = wxNewId();
const long Create_Passwords_gui_1_0Frame::WhereInPass2 = wxNewId();
const long Create_Passwords_gui_1_0Frame::WhereInPass3 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_CONTEXTHELPBUTTON2 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_STATICTEXT1 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_CHECKBOX5 = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_STATICTEXT5 = wxNewId();
const long Create_Passwords_gui_1_0Frame::idMenuQuit = wxNewId();
const long Create_Passwords_gui_1_0Frame::idMenuAbout = wxNewId();
const long Create_Passwords_gui_1_0Frame::ID_STATUSBAR1 = wxNewId();
//*)


	// decelerations
	int passlength,howMuchPasswords,fileSize=0,fileExist=0;
	std::string passlengthTMP,howMuchPasswordsTMP,wordTobeIncludedTMP,strToFile,strTMP;
	bool includeSymbols,includeNumbers,includeLowercaseCharacters,includeUppercaseCharacters,
    excludeSimilarCharacters,excludeSimilarNumbers,includeWordsWithMeaning,saveToTxt;







BEGIN_EVENT_TABLE(Create_Passwords_gui_1_0Frame,wxFrame)
    //(*EventTable(Create_Passwords_gui_1_0Frame)
    //*)
END_EVENT_TABLE()

Create_Passwords_gui_1_0Frame::Create_Passwords_gui_1_0Frame(wxWindow* parent,wxWindowID id)
{

wxTextValidator validator(wxFILTER_INCLUDE_CHAR_LIST);

wxArrayString list;

wxString valid_chars(wxT("0123456789"));
size_t len = valid_chars.Length();
for (size_t i=0; i<len; i++)
list.Add(wxString(valid_chars.GetChar(i)));

validator.SetIncludes(list);

//wxTextCtrl* textCtrl = new wxTextCtrl( this, wxID_ANY, _T(""), wxDefaultPosition, wxDefaultSize, 0,validator );
//PassLength = new wxTextCtrl(this, ID_TEXTCTRL3, _("8"), wxPoint(136,79), wxSize(112,22), 0, validator, _T("wxFILTER_NUMERIC"));
//HowMuchToGenerate = new wxTextCtrl(this, ID_TEXTCTRL1, _("1"), wxPoint(320,45), wxSize(112,22), 0, validator, _T("wxFILTER_NUMERIC"));

    //(*Initialize(Create_Passwords_gui_1_0Frame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, wxID_ANY, _("Nick name and password generator"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(595,624));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));
    Button1 = new wxButton(this, ID_BUTTON1, _("Generate password"), wxPoint(248,384), wxSize(112,22), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    PassContiner = new wxRichTextCtrl(this, ID_RICHTEXTCTRL1, wxEmptyString, wxPoint(120,408), wxSize(376,178), wxRE_MULTILINE|wxRE_READONLY, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
    wxRichTextAttr rchtxtAttr_1;
    rchtxtAttr_1.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
    wxFont Font_1(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    rchtxtAttr_1.SetFontFaceName(Font_1.GetFaceName());
    rchtxtAttr_1.SetFontSize(Font_1.GetPointSize());
    rchtxtAttr_1.SetFontStyle(Font_1.GetStyle());
    rchtxtAttr_1.SetFontUnderlined(Font_1.GetUnderlined());
    rchtxtAttr_1.SetFontWeight(Font_1.GetWeight());
    PassContiner->SetBasicStyle(rchtxtAttr_1);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Password length"), wxPoint(8,79), wxSize(96,24), 0, _T("ID_STATICTEXT2"));
    wxFont StaticText2Font(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("How many passwords to generate (Max 99)"), wxPoint(8,45), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    wxFont StaticText3Font(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText3->SetFont(StaticText3Font);
    HowMuchToGenerate = new wxTextCtrl(this, ID_TEXTCTRL1, _("1"), wxPoint(320,45), wxSize(112,22), 0, validator, _T("wxFILTER_NUMERIC"));
    HowMuchToGenerate->SetMaxLength(2);
    PassStrength = new wxStaticText(this, ID_STATICTEXT4, wxEmptyString, wxPoint(264,79), wxSize(152,24), 0, _T("ID_STATICTEXT4"));
    WordToBeIncluded = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxPoint(232,216), wxSize(112,22), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    WordToBeIncluded->SetMaxLength(8);
    RadioButtonNone = new wxRadioButton(this, ID_RADIOBUTTON1, _("None"), wxPoint(16,147), wxSize(64,24), wxRB_GROUP, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
    RadioButtonNone->SetValue(true);
    wxFont RadioButtonNoneFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    RadioButtonNone->SetFont(RadioButtonNoneFont);
    RadioButtonRandom = new wxRadioButton(this, ID_RADIOBUTTON2, _("Include a random word"), wxPoint(16,181), wxSize(184,24), 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
    wxFont RadioButtonRandomFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    RadioButtonRandom->SetFont(RadioButtonRandomFont);
    StaticText6 = new wxStaticText(this, ID_STATICTEXT7, _("Include words with meaning:"), wxPoint(8,113), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    wxFont StaticText6Font(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText6->SetFont(StaticText6Font);
    RadioButtonMenually = new wxRadioButton(this, ID_RADIOBUTTON3, _("Include a word of your own"), wxPoint(16,215), wxSize(208,24), 0, wxDefaultValidator, _T("ID_RADIOBUTTON3"));
    wxFont RadioButtonMenuallyFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    RadioButtonMenually->SetFont(RadioButtonMenuallyFont);
    IncludeSymbols = new wxCheckBox(this, ID_CHECKBOX1, _("Include Symbols ( e.g. @#$% )"), wxPoint(16,296), wxSize(240,24), 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    IncludeSymbols->SetValue(true);
    wxFont IncludeSymbolsFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    IncludeSymbols->SetFont(IncludeSymbolsFont);
    IncludeNumbers = new wxCheckBox(this, ID_CHECKBOX2, _("Include Numbers ( e.g. 123456 )"), wxPoint(272,296), wxSize(248,24), 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    IncludeNumbers->SetValue(true);
    wxFont IncludeNumbersFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    IncludeNumbers->SetFont(IncludeNumbersFont);
    IncludeLowercaseCharacters = new wxCheckBox(this, ID_CHECKBOX3, _("Include Lowercase Characters ( e.g. abcdefgh )"), wxPoint(16,328), wxSize(344,24), 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    IncludeLowercaseCharacters->SetValue(true);
    wxFont IncludeLowercaseCharactersFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    IncludeLowercaseCharacters->SetFont(IncludeLowercaseCharactersFont);
    IncludeUppercaseCharacters = new wxCheckBox(this, ID_CHECKBOX4, _("Include Uppercase Characters ( e.g. ABCDEFGH )"), wxPoint(16,352), wxSize(376,32), 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    IncludeUppercaseCharacters->SetValue(true);
    wxFont IncludeUppercaseCharactersFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    IncludeUppercaseCharacters->SetFont(IncludeUppercaseCharactersFont);
    ContextHelpButton1 = new wxContextHelpButton(this, wxID_CONTEXT_HELP, wxPoint(440,48), wxDefaultSize, wxBU_AUTODRAW);
    ContextHelpButton1->SetToolTip(_("Password length can be changed when you choose the option:\n\n3.Word will be included menually\n"));
    PassLength = new wxTextCtrl(this, ID_TEXTCTRL3, _("8"), wxPoint(136,79), wxSize(112,22), 0, validator, _T("wxFILTER_NUMERIC"));
    PassLength->SetMaxLength(3);
    RadioButtonLeft = new wxRadioButton(this, WhereInPass1, _("Left"), wxPoint(360,216), wxSize(56,24), wxRB_GROUP, wxDefaultValidator, _T("WhereInPass1"));
    RadioButtonLeft->SetValue(true);
    wxFont RadioButtonLeftFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    RadioButtonLeft->SetFont(RadioButtonLeftFont);
    RadioButtonMiddle = new wxRadioButton(this, WhereInPass2, _("Middle"), wxPoint(416,216), wxSize(72,24), 0, wxDefaultValidator, _T("WhereInPass2"));
    wxFont RadioButtonMiddleFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    RadioButtonMiddle->SetFont(RadioButtonMiddleFont);
    RadioButtonRight = new wxRadioButton(this, WhereInPass3, _("Right"), wxPoint(496,216), wxSize(64,24), 0, wxDefaultValidator, _T("WhereInPass3"));
    wxFont RadioButtonRightFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    RadioButtonRight->SetFont(RadioButtonRightFont);
    ContextHelpButton2 = new wxContextHelpButton(this, wxID_CONTEXT_HELP, wxPoint(568,216), wxDefaultSize, wxBU_AUTODRAW);
    ContextHelpButton2->SetToolTip(_("Choose where the word will be included in the password"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Nick name and password generator"), wxPoint(88,0), wxSize(440,32), 0, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(20,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    SaveToTxt = new wxCheckBox(this, ID_CHECKBOX5, _("Save to txt file"), wxPoint(16,392), wxSize(112,13), 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    SaveToTxt->SetValue(false);
    wxFont SaveToTxtFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial Narrow"),wxFONTENCODING_DEFAULT);
    SaveToTxt->SetFont(SaveToTxtFont);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT5, wxEmptyString, wxPoint(24,264), wxSize(568,13), 0, _T("ID_STATICTEXT5"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    Center();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Create_Passwords_gui_1_0Frame::OnButton1Click);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&Create_Passwords_gui_1_0Frame::OnHowMuchToGenerateText3);
    Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&Create_Passwords_gui_1_0Frame::OnWordToBeIncludedText);
    Connect(ID_RADIOBUTTON1,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&Create_Passwords_gui_1_0Frame::OnRadioButtonNoneSelect);
    Connect(ID_RADIOBUTTON2,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&Create_Passwords_gui_1_0Frame::OnRadioButtonRandomSelect);
    Connect(ID_RADIOBUTTON3,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&Create_Passwords_gui_1_0Frame::OnRadioButtonMenuallySelect);
    Connect(ID_TEXTCTRL3,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&Create_Passwords_gui_1_0Frame::OnPassLengthText);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Create_Passwords_gui_1_0Frame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Create_Passwords_gui_1_0Frame::OnAbout);
    Connect(wxEVT_MOTION,(wxObjectEventFunction)&Create_Passwords_gui_1_0Frame::OnMouseMove);
    //*)

  //zeroing all the booleans
    includeSymbols=includeNumbers=includeLowercaseCharacters=includeUppercaseCharacters=
    includeWordsWithMeaning=0;

    //zeroing all the integers
    howMuchPasswords=0;
    passlength=8;
    int TMPpasslength=passlength;


PassStrength->SetLabel("Weak password");
//wxFILTER_NUMERIC
//HowMuchToGenerate.SetValidator(0x0008);


RadioButtonLeft->Hide();
RadioButtonMiddle->Hide();
RadioButtonRight->Hide();
ContextHelpButton2->Hide();
WordToBeIncluded->Disable();

FileTestIfExist();
FileTestSize();


}



Create_Passwords_gui_1_0Frame::~Create_Passwords_gui_1_0Frame()
{



    //(*Destroy(Create_Passwords_gui_1_0Frame)
    //*)
}

void Create_Passwords_gui_1_0Frame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void Create_Passwords_gui_1_0Frame::OnAbout(wxCommandEvent& event)
{
    wxString msg = ("Create Passwords 1.0\nfor more questions send email to\nloleta.adro@gmail.com\n\n Created by XearoX");

    wxMessageBox(msg, _("About..."));
}



void Create_Passwords_gui_1_0Frame::OnButton1Click(wxCommandEvent& event)
{

// insert your code here


    //stirngs to use
    //passlengthTMP,howMuchPasswordsTMP,wordTobeIncludedTMP,strToFile,strTMP;

    //zeroing all the booleans
    //includeSymbols=includeNumbers=includeLowercaseCharacters=includeUppercaseCharacters=
    //includeWordsWithMeaning=0;

    //zeroing all the integers
    //howMuchPasswords=0;
    //passlength=8;

	//strTMP=OnlySymbols();
	//strTMP=OnlyUppercase();
	//strTMP=OnlyLowercase();
	//strTMP=OnlyNumbers();
	//strTMP=OnlyMiningWords();


////////from here we begin to work on the program our code///////////

	//get values
	howMuchPasswordsTMP=HowMuchToGenerate->GetValue(); //how much password to generate
	wordTobeIncludedTMP=WordToBeIncluded->GetValue();//get the Word To Be Included

	includeSymbols=IncludeSymbols->GetValue(); //getting checkbox Include Symbols status 1 or 0
	includeNumbers=IncludeNumbers->GetValue(); //getting checkbox Include Numbers status 1 or 0
	includeLowercaseCharacters=IncludeLowercaseCharacters->GetValue(); //getting checkbox Include Lowercase Characters status 1 or 0
	includeUppercaseCharacters=IncludeUppercaseCharacters->GetValue(); //getting checkbox Include Symbols status 1 or 0
    passlengthTMP=PassLength->GetValue();
    saveToTxt=SaveToTxt->GetValue(); //getting checkbox save or not status 1 or 0


    string tmp;
    wxString wxstring;

    //geting the value of how much passwords to generate edit text
    wxstring=HowMuchToGenerate->GetValue();
    wxstring.ToStdString();
    howMuchPasswordsTMP=wxstring;




        if(includeNumbers==0&&includeSymbols==0&&includeLowercaseCharacters==0&&includeUppercaseCharacters==0&&RadioButtonNone->GetValue()==1)
        {
           StaticText4->SetLabel("Please check mark Of these options,symbols,numbers,lowercase,uppercase");
           Button1->Disable();
           return ;
        }


        else
        {

        passlength=stoi(passlengthTMP);

        //from  string to ineteger
        howMuchPasswords=stoi(howMuchPasswordsTMP);

        //clear password continer when button of generate password is clicked
        PassContiner->Clear();

        //how much passwords to generate
       for(int i=0;i<howMuchPasswords;i++)
       {
           /////////////////////////if Radio Button None is chacked////////////////////////////////
           if((RadioButtonNone->GetValue())==true)
           {
              passlength=wxAtoi(PassLength->GetValue());
              //RadioBtnNoneIsChecked();
              strTMP=RandomAddCharsToStr(strTMP,passlength);

           }


           /////////////////////////if Radio Button Random is chacked////////////////////////////////

           else if((RadioButtonRandom->GetValue())==true)
           {



            if(includeNumbers==0&&includeSymbols==0&&includeLowercaseCharacters==0&&includeUppercaseCharacters==0)
            {
                wxMessageBox("Please check mark Of these options,symbols,numbers,lowercase,uppercase");
                return;
            }


             else{
                OnlyMiningWords();

                    /*this is doing lower to upper randommally when randomally is cheaked
                    and upper case is chacked
                    */
                    if(includeUppercaseCharacters) /////////if to include upper case
                    for(int i=0;i<strTMP.size();i++)
                    {
                        int c=0;
                        c=rand()%2; ///its now or 1 or 0
                        if(c)
                        if(strTMP.at(i)>='a'&&strTMP.at(i)<='z') strTMP.at(i)-=32;

                    }





               // passlength1=(passlength-(strTMP.size()));
               int tmp,tmplen;
               tmp=strTMP.size();


                    if(passlength-tmp<0)
                    {
                    wxMessageBox(wxString::Format(wxT("passlength:%i-strTMP.size:%i===%i"),passlength,tmp,passlength-tmp));
                    PassContiner->Clear();
                    return;
                    }

                    int c=0;

                    c=rand()%3+1;
                    switch(c)
                    {
                        ///////////case 1///////////
                        case 1:///string will be left
                        {

                        tmplen=passlength;
                        passlength=passlength-tmp;
                       // RadioBtnRndIsChecked();
                        strTMP=RandomAddCharsToStr(strTMP,passlength);
                        passlength=tmplen;break;
                        }
                        ////////////case 2///////////
                        case 2:///string will be center
                            {

                               int l=0,w=0,r=0; //l= password length ,w= word length , r = result
                               l=passlength;
                               w=strTMP.size();
                               r=l-w; //resutl = password - word
                               if(r<=0)
                               {

                                 wxMessageBox(wxString::Format(wxT("passlength:%i-strTMP.size:%i===%i"),l,w,r));
                                PassContiner->Clear();
                                 return;
                               }

                               string tmp;
                               //strTMP+=RandomAddCharsToStr(tmp,r);

                               if(r%2!=0)
                               {
                                   r=r/2;
                                   tmp=RandomAddCharsToStr(tmp,r);
                                   tmp+=strTMP;
                                   tmp=RandomAddCharsToStr(tmp,r);
                                   tmp=RandomAddCharsToStr(tmp,1);
                                   strTMP=tmp;
                               }

                               else
                               {
                                   r=r/2;
                                   tmp=RandomAddCharsToStr(tmp,r);
                                   tmp+=strTMP;
                                   tmp=RandomAddCharsToStr(tmp,r);
                                   strTMP=tmp;
                               }


                               if(strTMP.size()>passlength)
                               {
                                wxMessageBox(wxString::Format(wxT("passlength:%i-strTMP.size:%i===%i"),l,strTMP.size(),r));
                                PassContiner->Clear();
                                 return;
                               }

                               break;
                            }

                        ////////////case 3 //////////////
                        case 3://string will be right
                            {

                                int l=0,w=0,r=0;
                                l=passlength;
                                w=strTMP.size();
                                r=l-w;

                                string tmp;
                                tmp=RandomAddCharsToStr(tmp,r);
                                tmp+=strTMP;
                                strTMP=tmp;
                                break;
                            }



                    }



                  }
              }



           /////////////////////////if Radio Button Menually is chacked////////////////////////////////
           //((RadioButtonMenually->GetValue())==true)
           else
           {
            if(includeNumbers==0&&includeSymbols==0&&includeLowercaseCharacters==0&&includeUppercaseCharacters==0)
            {
                wxMessageBox("Please check mark Of these options,symbols,numbers,lowercase,uppercase");
                return;
            }

            if(WordToBeIncluded->GetValue().empty())
            {
              wxMessageBox("Please enter a word to be included in your password");
                return;
            }

             else{
                strTMP=WordToBeIncluded->GetValue().ToStdString();

                int len,lenTMP;
                len=(passlength-(strTMP.size()));
                if(len<0) //if password length is smaller than zero
                {
                wxMessageBox("Password length cannot be less than the word you included");
                PassLength->SetValue(wxString::Format(wxT("%i"),strTMP.size()));
                PassContiner->Clear();
               return;
                }

                    if(RadioButtonLeft->GetValue())
                    {

                    lenTMP=passlength;
                    passlength=len;
                    strTMP=RandomAddCharsToStr(strTMP,passlength);
                    passlength=lenTMP;
                    }

                        else if(RadioButtonMiddle->GetValue())
                        {
                               int l=0,w=0,r=0; //l= password length ,w= word length , r = result
                                l=passlength=wxAtoi(PassLength->GetValue());
                                strTMP=WordToBeIncluded->GetValue().ToStdString();
                               w=strTMP.size();
                               r=l-w; //resutl = password - word
                               if(r<0)
                               {

                                 wxMessageBox(wxString::Format(wxT("passlength:%i-strTMP.size:%i===%i"),l,w,r));
                                PassContiner->Clear();
                                 return;
                               }
                               string tmp;


                               if(r%2!=0)
                               {
                                   r=r/2;
                                   tmp=RandomAddCharsToStr(tmp,r);
                                   tmp+=strTMP;
                                   tmp=RandomAddCharsToStr(tmp,r);
                                   tmp=RandomAddCharsToStr(tmp,1);
                                   strTMP=tmp;
                               }

                               else
                               {
                                   r=r/2;
                                   tmp=RandomAddCharsToStr(tmp,r);
                                   tmp+=strTMP;
                                   tmp=RandomAddCharsToStr(tmp,r);
                                   strTMP=tmp;
                               }



                           }

                         else
                          {

                                int l=0,w=0,r=0;
                                l=passlength=wxAtoi(PassLength->GetValue());
                                strTMP=WordToBeIncluded->GetValue().ToStdString();
                                w=strTMP.size();
                                r=l-w;

                                string tmp;
                                tmp=RandomAddCharsToStr(tmp,r);
                                tmp+=strTMP;
                                strTMP=tmp;
                          }
                }
             }

           PasswordSaveToText();
           PassContiner->AppendText(wxString::Format(wxT("%s\n"),strTMP));
           strTMP.clear();
       }
    }

}






////////////////My functions/////////////////////////////////

////////////////OnlySymbols//////////////////////////////////
int OnlySymbols()
{
	int ch;



	ch=rand()%4+1;

	switch(ch)
	{
		case 1:ch=rand()%15+33;break;
		case 2:ch=rand()%7+58;break;
		case 3:ch=rand()%6+91;break;
		case 4:ch=rand()%4+123;break;
	}


    return ch;
}

////////////////OnlyUppercase//////////////////////////////////

int OnlyUppercase()
{
 	int ch;

	ch=rand()%26+65;


  return ch;
}


////////////////OnlyLowercase//////////////////////////////////
int OnlyLowercase()
{
int ch;

	ch=rand()%26+97;


  return ch;
}




////////////////OnlyNumbers//////////////////////////////////
int OnlyNumbers()
{
	int ch;


  	ch=rand()%10+48;


   return ch;
}



//////////OnlyMiningWords//////////
std::string OnlyMiningWords()
{

    int i=0,line_no=0;
    string line;
    ifstream fileWords("word_list_58000.txt");
    i=rand()%fileSize+1;

    if (fileWords.is_open())
    {

        while (line_no != i && getline(fileWords, line))
        {
           ++line_no;

           if(line.size()>=passlength) continue;

           strTMP=line;
        }
         return strTMP;

    }

     else
     {
        strTMP="";
        return strTMP;
     }


}




string RandomAddCharsToStr(string tmp,int len)
{
     for(int i=0;i<len;i++)
               {
                int c;
                  c=rand()%4+1;
                    switch(c)
                    {
                 //////////////case1///////////////
                     case 1:
                        {
                         if(includeSymbols==true)
                         {
                           tmp+=OnlySymbols();
                            break;
                         }
                            else
                            {
                            i--;
                            break;
                            }
                         }
                      ///////////case 2/////////////
                        case 2:
                        {
                         if(includeNumbers==true)
                         {
                           tmp+=OnlyNumbers();
                            break;
                         }
                            else
                            {
                            i--;
                            break;
                            }
                         }

                       ///////////case 3/////////////
                        case 3:
                        {
                         if(includeLowercaseCharacters==true)
                         {
                           tmp+=OnlyLowercase();
                            break;
                         }
                            else
                            {
                            i--;
                            break;
                            }
                         }


                    ///////////case 4/////////////
                        case 4:
                        {
                         if(includeUppercaseCharacters==true)
                         {
                           tmp+=OnlyUppercase();
                            break;
                         }
                            else
                            {
                            i--;
                            break;
                            }
                         }
                    }
               }

               return tmp;
}


void Create_Passwords_gui_1_0Frame::OnWordToBeIncludedText(wxCommandEvent& event)
{
    string str;
    int Word;
    passlengthTMP=passlength;

    str=WordToBeIncluded->GetValue().ToStdString();
    Word=str.size();

    //PassContiner->AppendText(wxString::Format(wxT("Word=%i\n"),Word));

    str=PassLength->GetValue().ToStdString();
    passlength=stoi(str);

    //PassContiner->AppendText(wxString::Format(wxT("passlength=%i\n"),passlength));

    if((RadioButtonMenually->GetValue()==1)&&Word>passlength)
    {
       // PassContiner->AppendText(wxString::Format(wxT("Word=true->%i\n"),Word));
        PassLength->SetValue(wxString::Format(wxT("%i"),Word));
    }

    if(wxAtoi(PassLength->GetValue())<16) PassStrength->SetLabel("Weak password");
    else if(wxAtoi(PassLength->GetValue())>16&&wxAtoi(PassLength->GetValue())<128) PassStrength->SetLabel("Strong password");
    else PassStrength->SetLabel("Unbelevibale password");


}

void FileTestSize()
{
    fileSize=0;
    std::ifstream file("word_list_58000.txt");
    std::string str;
    while (std::getline(file, str))
    {
        fileSize++;
    }


}

void FileTestIfExist()
{
    fileExist=0;
    ifstream fileWords("word_list_58000.txt");
    if (fileWords.is_open())
    {
        fileExist=1;
    }



    else
    {
      wxMessageBox(wxString::Format(wxT("File word_list_58000.txt doesn't Exist")));
         ofstream myfile;
        myfile.open ("word_list_58000.txt");
        myfile<<"test";
        myfile.close();
       wxMessageBox(wxString::Format(wxT("Now the file word_list_58000.txt is exist\n write inside words you want to be included randomly")));

       exit(1);
    }
}



void PasswordSaveToText()
{
    //SaveToTxt
    if(saveToTxt==1)
    {
     ofstream myfile;
        myfile.open ("Passwords.txt",std::ios_base::app);
        myfile<<strTMP<<std::endl;
        myfile.close();
    //wxMessageBox(wxString::Format(wxT("File Saved")));
    }
}





void Create_Passwords_gui_1_0Frame::OnRadioButtonMenuallySelect(wxCommandEvent& event)
{
    RadioButtonLeft->Show();
    RadioButtonMiddle->Show();
    RadioButtonRight->Show();
    ContextHelpButton2->Show();
    WordToBeIncluded->Enable();
}

void Create_Passwords_gui_1_0Frame::OnRadioButtonNoneSelect(wxCommandEvent& event)
{
  RadioButtonLeft->Hide();
  RadioButtonMiddle->Hide();
  RadioButtonRight->Hide();
  ContextHelpButton2->Hide();
  WordToBeIncluded->Disable();

}




void Create_Passwords_gui_1_0Frame::OnRadioButtonRandomSelect(wxCommandEvent& event)
{
RadioButtonLeft->Hide();
RadioButtonMiddle->Hide();
RadioButtonRight->Hide();
ContextHelpButton2->Hide();
WordToBeIncluded->Disable();
}

void Create_Passwords_gui_1_0Frame::OnPassLengthText(wxCommandEvent& event)
{
      bool canBeContinue=true;

      if(PassLength->GetValue().empty()||wxAtoi(PassLength->GetValue())<3)
        {
            PassStrength->SetLabel("Password length must be greater then 2");
            Button1->Disable();
            canBeContinue==false;
            return ;
        }

    if(wxAtoi(PassLength->GetValue())<16) PassStrength->SetLabel("Weak password");
    else if(wxAtoi(PassLength->GetValue())>16&&wxAtoi(PassLength->GetValue())<128) PassStrength->SetLabel("Strong password");
    else PassStrength->SetLabel("Unbelevibale password");



    if(canBeContinue==true)
    {
          Button1->Enable();
    }
}

//if there is a motion
void Create_Passwords_gui_1_0Frame::OnMouseMove(wxMouseEvent& event)
{
    //bool canBeContinue=true;
    //wxMessageBox(wxString::Format(wxT("new motion")));
     /*   if(HowMuchToGenerate->GetValue().empty()||wxAtoi(HowMuchToGenerate->GetValue())<1)
        {
            PassStrength->SetLabel("how many passwords must be greater then 0");
            Button1->Disable();
            canBeContinue=false;
            return ;
        }

        if(PassLength->GetValue().empty()||wxAtoi(PassLength->GetValue())<3)
        {
            PassStrength->SetLabel("Password length must be greater then 2");
            Button1->Disable();
            canBeContinue=false;
            return ;
        }

/*
        if(canBeContinue==true)
        {
           Button1->Enable();
        }*/

/*
    if(wxAtoi(PassLength->GetValue())<16) PassStrength->SetLabel("Weak password");
    else if(wxAtoi(PassLength->GetValue())>16&&wxAtoi(PassLength->GetValue())<128) PassStrength->SetLabel("Strong password");
    else PassStrength->SetLabel("Unbelevibale password");
*/
}


//when text change occurs in howmuchtogenerate this function is called
void Create_Passwords_gui_1_0Frame::OnHowMuchToGenerateText3(wxCommandEvent& event)
{
    bool canBeContinue=true;

       if(HowMuchToGenerate->GetValue().empty()||wxAtoi(HowMuchToGenerate->GetValue())<1)
        {
            PassStrength->SetLabel("how many passwords to generate must be greater then 0");
            Button1->Disable();
            canBeContinue=false;
            return ;
        }


        if(canBeContinue==true)
        {
          Button1->Enable();
        }

}


