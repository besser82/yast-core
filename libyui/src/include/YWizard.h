/*---------------------------------------------------------------------\
|								       |
|		       __   __	  ____ _____ ____		       |
|		       \ \ / /_ _/ ___|_   _|___ \		       |
|			\ V / _` \___ \ | |   __) |		       |
|			 | | (_| |___) || |  / __/		       |
|			 |_|\__,_|____/ |_| |_____|		       |
|								       |
|				core system			       |
|							 (C) SuSE GmbH |
\----------------------------------------------------------------------/

  File:	      YWizard.h

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/

#ifndef YWizard_h
#define YWizard_h

#include "YContainerWidget.h"
#include <ycp/YCPString.h>
#include <ycp/YCPValue.h>

class YMacroRecorder;

#define YWizardID			"wizard"
#define YWizardContentsReplacePointID	"contents"

/**
 * @short Implementation of the SelectionBox widget.
 */
class YWizard: public YContainerWidget
{
public:

    /**
     * Constructor
     */
    YWizard( const YWidgetOpt & opt,
	     const YCPValue & backButtonId,	const YCPString & backButtonLabel,
	     const YCPValue & abortButtonId,	const YCPString & abortButtonLabel,
	     const YCPValue & nextButtonId,	const YCPString & nextButtonLabel  );

    /**
     * Returns a descriptive name of this widget class for logging,
     * debugging etc.
     */
    virtual char *widgetClass() { return "YWizard"; }

    /**
     * Generic direct access to implementation-specific functions.
     * Derived classes should implement this.
     **/
    virtual YCPValue command( const YCPTerm & command );

    /**
     * Implements UI::QueryWidget() for this widget class.
     */
    YCPValue queryWidget( const YCPSymbol & property );


protected:

    /**
     * Returns the current tree selection or an empty string if nothing is
     * selected or there is no tree. 
     **/
    virtual YCPString currentTreeSelection() { return YCPString( "" ); }

    
    // Data members

    YCPValue 	_backButtonId;
    YCPString 	_backButtonLabel;
    YCPValue 	_abortButtonId;
    YCPString 	_abortButtonLabel;
    YCPValue 	_nextButtonId;
    YCPString 	_nextButtonLabel;
};


#endif // YWizard_h