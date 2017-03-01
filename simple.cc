#include <gtkmm.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <regex>

Gtk::Window* pWindow = nullptr;
Gtk::FileChooserDialog* filechooser = nullptr;
Gtk::Entry* pxres = nullptr;
Gtk::Entry* pyres = nullptr;
Gtk::Button* filebutton = nullptr;
Gtk::Button* gobutton = nullptr;
Gtk::Button* okbuttonfile = nullptr;
Gtk::Button* cancelbuttonfile = nullptr;
Gtk::Entry* filein = nullptr;
Gtk::Entry* fileout = nullptr;
Gtk::Entry* startfrom = nullptr;
Gtk::Entry* duration = nullptr;
Gtk::CheckButton* rescheck = nullptr;
Gtk::CheckButton* startfromcheck = nullptr;
Gtk::CheckButton* durationcheck = nullptr;
Gtk::CheckButton* mutecheck = nullptr;
Gtk::Dialog* messagedialog = nullptr;
Gtk::Label* dialoglabel = nullptr;

static void dothething()
{

	std::string command = "xterm -e ffmpeg ";

	std::cout << command << std::endl;

	if(startfromcheck->get_active())
	{
    command += "-ss "+startfrom->get_text()+" ";
	}

	std::cout << command << std::endl;

	if(durationcheck->get_active()){
	    command += "-t "+duration->get_text()+" ";
	}

	std::cout << command << std::endl;

	command +="-i \""+filein->get_text()+"\" -c:v libvpx -crf 32 -b:v 900K -threads 1 ";

	std::cout << command << std::endl;

	if(mutecheck->get_active())
	{
	    command += "-an ";
	}
	else
	{
	    command += "-c:a libvorbis ";
	}

	std::cout << command << std::endl;

	if(rescheck->get_active())
	{
		command += "-vf scale="+pxres->get_text()+":"+pyres->get_text();
	}
	else
	{
		command += "-vf scale=-1:-1";
	}

	std::cout << command << std::endl;

	command += " -y -nostdin \""+fileout->get_text()+"\"";

	std::cout << command << std::endl;

	const char* p = command.c_str();
	system(p);


	dialoglabel->set_text(fileout->get_text());
	messagedialog->run();
	messagedialog->hide();

}

static void restoggled()
{
	if(rescheck->get_active())
	{
		pyres->set_sensitive(true);
		pxres->set_sensitive(true);

	}
	else
	{
		pyres->set_sensitive(false);
		pxres->set_sensitive(false);
	}
}

static void starttoggled()
{
	if(startfromcheck->get_active())
	{
		startfrom->set_sensitive(true);

	}
	else
	{
		startfrom->set_sensitive(false);
	}
}

static void durtoggled()
{
	if(durationcheck->get_active())
	{
		duration->set_sensitive(true);

	}
	else
	{
		duration->set_sensitive(false);
	}
}

static
void on_file_button_clicked()
{
	//int result = std::stoi((std::string)pEntry1->get_text()) + std::stoi((std::string)pEntry2->get_text());
	//pLabel->set_text(std::to_string(result));
	
	int result = filechooser->run();
	if (result == 1)
	{
		std::string filename = filechooser->get_filename();

		const std::regex file("(.*)(\\..*$)");
        std::smatch match;
        std::string ma;

        if(regex_search(filename, match, file)){

            ma = match[1].str();
        }

        fileout->set_text(ma+".webm");

		filein->set_text(filename);
	}
	filechooser->hide();
}


int main(int argc, char *argv[])
{

	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  auto refBuilder = Gtk::Builder::create();
  refBuilder->add_from_file("glade.glade");

  // Windows
  refBuilder->get_widget("mainwindow", pWindow);
  refBuilder->get_widget("dialog", messagedialog);
  //refBuilder->get_widget("terminalw", pWindowTerm);
  refBuilder->get_widget("filechooser", filechooser);

  // Labels
  refBuilder->get_widget("dialoglabel", dialoglabel);

  // SpinButtons
  refBuilder->get_widget("xspinbutton", pxres);
  refBuilder->get_widget("yspinbutton", pyres);

  // Entries
  refBuilder->get_widget("filein", filein);
  refBuilder->get_widget("fileout", fileout);
  refBuilder->get_widget("startfrom", startfrom);
  refBuilder->get_widget("duration", duration);
  
  // Buttons
  refBuilder->get_widget("okbuttonfile", okbuttonfile);
  refBuilder->get_widget("filebutton", filebutton);
  refBuilder->get_widget("gobutton", gobutton);

  // Checkboxes
  refBuilder->get_widget("rescheck", rescheck);
  refBuilder->get_widget("startfromcheck", startfromcheck);
  refBuilder->get_widget("durationcheck", durationcheck);
  refBuilder->get_widget("mutecheck", mutecheck);

  if(pWindow)
  {
  	filebutton->signal_clicked().connect( sigc::ptr_fun(on_file_button_clicked) );
  	rescheck->signal_toggled().connect( sigc::ptr_fun(restoggled) );
  	startfromcheck->signal_toggled().connect( sigc::ptr_fun(starttoggled) );
  	durationcheck->signal_toggled().connect( sigc::ptr_fun(durtoggled) );
  	gobutton->signal_clicked().connect( sigc::ptr_fun(dothething) );

		pWindow->move(Gdk::screen_width() / 2 - 300, Gdk::screen_height() / 2 - 200);
    app->run(*pWindow);
  }

}