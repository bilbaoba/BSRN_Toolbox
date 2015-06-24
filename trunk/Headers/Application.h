/* Application.h              */
/* 2013-05-15                 */
/* Dr. Rainer Sieger          */

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include <QTextEdit>
#include <QTextCodec>
#include <QTextStream>
#include <QStringListModel>
#include <QListView>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QCloseEvent>
#include <QProcess>
#include <QTimer>
#include <QMimeData>
#include <QDesktopServices>
#include <QMessageBox>
#include <QProgressBar>
#include <QProgressDialog>
#include <QStatusBar>
#include <QSettings>
#include <QPointer>
#include <QErrorMessage>

#include "Globals.h"
#include "Webfile.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class QAction;
class QLabel;
class QProgressDialog;
class QProgressBar;
class QTimer;
class QDateTime;
class QUrl;
class QTextEdit;
class QStringListModel;
class QListView;
class QTableWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_CLASSINFO( "author", "Rainer Sieger" )
    Q_CLASSINFO( "url", "http://www.pangaea.de" )

/* @brief Array fuer die Verwaltung des Instrumentwechseldatums */

    struct structParameter
    {
        int ParameterID;			//!< Parameter ID
        int MethodID;				//!< Method ID
        QDateTime DateTime;			//!< Date/Time des letzten Instrumentwechsels
    };

/* @brief Array fuer die Verwaltung der Methoden */

    struct structMethod
    {
        int StationID;				//!< Station ID
        QString SerialNumber;		//!< Geraete Seriennummer
        int WRMCnumber;				//!< WRMC Nummer
        int MethodID;				//!< Method ID
    };

/* @brief Array fuer die Verwaltung der Stationsleiter */

    struct structStaff
    {
        QString StationScientist;	//!< Name des Stationsleiter
        int StaffID;				//!< Staff ID
    };

/* @brief Array fuer die Verwaltung der Stationen */

    struct structStation
    {
        int StationID;				//!< Station ID
        QString EventLabel;			//!< Kurzname der Station wird als Event label benutzt
        QString StationName;		//!< Stationsname
        int InstituteID;			//!< Institut ID
    };

/* @brief Array fuer die Verwaltung der Datensaetze */

    struct structDataset
    {
        QString ExportFilename;		//!< Export filename
        int DatasetID;	    		//!< Dataset ID
    };


public:
    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

    int         gi_EOL;                 //!< End-of-Line Zeichen fuer die Outputdateien
    int         gi_Codec;               //!< Zeichenkodierung
    int         gi_Extension;           //! Dateierweiterung fuer Ausgabedateien
    int         gi_NumOfProgramStarts;  //!< Anzahl der Programmstarts

    int			gi_ActionNumber;        //!< Die ActionNumber wird bei jedem angewandenten Tool um 1 erhoeht.
    int			gi_SkipNFirstLines;     //!< Anzahl der Zeilen, die beim Verbinden von Dateien am Anfang uebersprungen werden sollen.
    int         gi_FieldDelimiter;      //!< Felddelimiter fr den Format Converter
    int         gi_FieldWidth;          //!< Feldbreite fr den Format Converter
    int         gi_FieldAlignment;      //!< Textausrichtung fr den Format Converter

    QString		gs_DownloadPath;        //!< Pfad fuer die Ablage der Station-to-archive Dateien
    QString		gs_User;                //!< Accountname
    QString		gs_Password;            //!< Password
    QString		gs_FTPServer;           //!< Adresse des Servers

    bool		gb_DecompressFiles;		//!< Wenn true werden die Dateien mit GZip entpackt
    bool		gb_CheckFiles;			//!< Wenn true werden die Dateien mit BSRN_fcheck geprueft
    bool		gb_CheckAvailability;	//!< Wenn true wird nur die Verfuegbarkeit der Dateien geprueft
    bool		gb_DeleteOriginalFiles;	//!< Wenn true werden die Original-Dateien nach dem Verbinden geloescht.
    bool        gb_OverwriteDataset;    //!< Wenn true wird der Datensatz berschrieben.

    bool		gb_Station[MAX_NUM_OF_STATION+1];	//!< Array von Flags, wenn Flag[i] = true werden die Datei der ausgewaehlten Station geladen
    bool		gb_Month[MAX_NUM_OF_MONTH+1];		//!< Array von Monaten
    bool		gb_Year[MAX_NUM_OF_YEAR+1];			//!< Array von Jahren

    QString     gs_MissingValue;    //!< Missing value fr den Format Converter
    QString		gs_FilenameFormat;	//!< Bestimmt in die Form des automatisch erzeugten neuen Dateinamens. \%a = aktuelle Actionnumber, \%N = Dateiname.
    QString		gs_Path;			//!< Der zuletzt verwendete Pfad.
    QString     gs_Version;         //!< Programmversion

    QStringList gsl_FilenameList;	//!< Liste aller InputDateinamen incl. Pfad.

    bool        gb_CheckPhysicallyPossibleLimits; //!< If true perform quality check "Physically Possible Limits"
    bool        gb_CheckExtremelyRareLimits;      //!< If true perform quality check "Extremely Rare Limits"
    bool        gb_CheckComparisons;              //!< If true perform quality check "Comparisons"
    QString     gs_AuxiliaryDataAlgorithm;        //!< Algorithm to use for determining auxiliary data during quality check
    bool        gb_OutputCodes;                   //!< If true write quality codes to file after quality check
    bool        gb_OutputCleanedValues;           //!< If true write cleaend values to file after quality check
    bool        gb_OutputOriginalValues;          //!< If true write original values to file after quality check
    bool        gb_OutputAuxiliaryData;           //!< If true write calculated auxiliary data to file after quality check
    bool        gb_OutputOneFile;                 //!< If true write all data from quality check to one file

protected:
    void dragEnterEvent( QDragEnterEvent *event );
    void dropEvent( QDropEvent *event );
    void closeEvent( QCloseEvent *event );
    void onError( const int err );

signals:
    void finishedBuildFilelist( bool );

private slots:
    int  chooseFile();
    int  chooseFiles();
    int  chooseFolder( const QString& Folder = "" );
    int  saveFile();
    int  saveFileAs();
    void about();
    void hideWindow();
    void newWindow();
    void displayHelp();
    void clearStatusMessage();
    int  incProgress( const int Step );

// Station-to-arvive
    void doDownloadStationToArchiveFiles();
    void doCheckStationToArchiveFiles();

// Metadata
    void doFileIDConverter();
    void doScientistIDConverter();
    void doMessagesConverter();
    void doStationDescriptionConverter();
    void doRadiosondeEquipmentConverter();
    void doOzoneEquipmentConverter();
    void doStationHistoryConverter();
    void doRadiationInstrumentsConverter();
    void doAssignmentConverter();
    void doCreateReferenceImportFile();
    void doAllMetadataConverter();

//  Data
    void doBasicMeasurementsConverter( const bool Import = false );
    void doOtherMinuteMeasurementsConverter();
    void doUltraVioletMeasurementsConverter( const bool Import = false );
    void doSYNOPConverter( const bool Import = false );
    void doRadiosondeMeasurementsConverter( const bool Import = false );
    void doOzoneMeasurementsConverter( const bool Import = false );
    void doExpandedMeasurementsConverter( const bool Import = false );
    void doOtherMeasurementsAtXmConverter( const bool Import = false, const int Height = 10 );
    void doOtherMeasurementsAt10mConverter();
    void doOtherMeasurementsAt30mConverter();
    void doOtherMeasurementsAt300mConverter();
    void doAllDataConverter();

//  Import
    void doBasicMeasurementsImportConverter();
    void doUltraVioletMeasurementsImportConverter();
    void doSYNOPImportConverter();
    void doRadiosondeMeasurementsImportConverter();
    void doOzoneMeasurementsImportConverter();
    void doExpandedMeasurementsImportConverter();
    void doOtherMeasurementsAt10mImportConverter();
    void doOtherMeasurementsAt30mImportConverter();
    void doOtherMeasurementsAt300mImportConverter();
    void doAllImportConverter();
    void doSetOverwriteDatasetFlag();

//  Tools
    void doConcatenateFiles();
    void doWinConvertEOL();
    void doMacOSConvertEOL();
    void doCompressFile();
    void doConvertUnformatted();
    void doConvertFormatted();

//  Quality management
    void doQualityCheckRecommendedV20();
    //void doQualityCheckTechnicalReport1();
    //void doQualityCheckUserDefined();

private:
    QStringList expandCommandline();
    QStringList renameFiles( const QStringList Filename, const QString &searchStr, const QString &replaceStr );
    bool buildFilename( const int ActionNumber, const QString &FilenameFormat, const int Extension, const QString &Filename, QString &FilenameIn, QString &FilenameOut );
    bool existsFirstFile( const int ActionNumber, const QString &FilenameFormat, const int Extension, QStringList &FilenameList );
    bool isEmptyLine( const QString &String );
    int NumOfSections( const QString &String );
    int buildFileList( QStringList &FilenameList, const QString &Filename, const bool extractZipFile = true );
    int calcFileSizeClass( const QString &FilenameIn, const int NumOfFiles, const int lowerLimit = 100, const int upperLimit = 1000 );
    int copyStringList( const QStringList InStringList, QStringList &OutStringList, const QString &s_Pattern = "*" );
    int emptyDir( const QString &Dir );
    int extractZipFile( const QString &Filename, const bool createNewDir = false, const bool delZipFile = false );
    int incFileProgress( const int NumOfFiles, const int FileNumber );
    int incProgress( const int NumOfFiles, const int Step );
    int readFile( const QString &FilenameIn, QStringList &Input, const int Codec = -1, const int NumOfFiles = 0, const qint64 Bytes = 0 );
    int removeFile( const QString &Filename );
    int downloadFile( const QString &Url, const QString &absoluteFilePath );
    unsigned int incProgress( const int NumOfFiles, const unsigned int filesize, const unsigned int length, const QString &InputStr );
    void appendItem( QStringList &List, const QString &Item, const QString &SS = "", const QString &RS = "" );
    void clearFilenameList( int &ActionNumber, QStringList &FilenameList );
    void clearList( QStringList& List );
    void clearMessage();
    void createActions();
    void createMenus();
    void createStatusBar();
    void endTool( const int err, const int stopProgress, int &ActionNumber, const QString &FilenameFormat, const int Extension, QStringList &FilenameList, const QString &doneMessage = "Done", const QString &canceledMessage = "Converter was canceled", const bool clearList = false, const bool incActionNumber = true );
    void initFileProgress( const int NumOfFiles, const QString &FilenameIn, const QString &MessageText );
    void initProgress( const int NumOfFiles, const QString &Filename, const QString &MessageText, const int totalNumberOfSteps );
    void initProgress( const int totalNumberOfSteps );
    void listDir( QStringList &Filename, const QString &Directory, const bool extractZipFile = true );
    void loadPreferences();
    void resetFileProgress( const int NumOfFiles );
    void resetProgress( const int NumOfFiles = 0 );
    void savePreferences();
    void setNormalCursor();
    void setStatusBar( const QString &Message = "", const int seconds = 0 );
    void setStatusBarFileInProgress( const QString &Filename, const QString &Message = "", const int i_seconds = 0 );
    void setWTitle( const int ActionNumber, const QString &FilenameFormat, const int Extension, const QStringList &sl_FilenameList );
    void setWaitCursor();
    void showFilenameList( const int ActionNumber, const QString &FilenameFormat, const int Extension, const QStringList FilenameList );
    void showList( const QStringList List );
    void showMessage( const QString &Message, QStringList &MessageList );
    void wait( const int msec );

    QString getApplicationName( const bool replaceUnderline = false );
    QString getDataLocation();
    QString getDocumentDir();
    QString getPreferenceFilename();
    QString getVersion();
    QString setEOLChar( const int EOL );
    QString setExtension( const int Extension );

    bool warning(const QString & Message, const QString & Title = tr("Warning"));

// Station-to-archive
    int downloadStationToArchiveFiles( structStation *Station_ptr, const QString& FilenameOut, const QString& FTPServer, const QString& User, const QString& Password, const bool DecompressFiles, const bool CheckFiles, const bool CheckAvailability, bool Station[MAX_NUM_OF_STATION+1], bool Month[MAX_NUM_OF_MONTH+1], bool Year[MAX_NUM_OF_YEAR+1] );

// Metadata
    int FileIDConverter( const QString& FilenameIn, QStringList& FilenameOut, structStation *Station_ptr, const int NumOfFiles );
    int ScientistIDConverter( const QString& FilenameIn, QStringList& FilenameOut, structStaff *Staff_ptr, structStation *Station_ptr, const int NumOfFiles );
    int MessagesConverter( const QString& FilenameIn, QStringList& FilenameOut, structStation *Station_ptr, const int NumOfFiles );
    int StationDescriptionConverter( const QString& FilenameIn, QStringList& FilenameOut, structStation *Station_ptr, const int NumOfFiles );
    int RadiosondeEquipmentConverter( const QString& FilenameIn, QStringList& FilenameOut, structMethod *Method_ptr, structStation *Station_ptr, const int NumOfFiles );
    int OzoneEquipmentConverter( const QString& FilenameIn, QStringList& FilenameOut, structMethod *Method_ptr, structStation *Station_ptr, const int NumOfFiles );
    int StationHistoryConverter( const QString& FilenameIn, QStringList& FilenameOut, structStation *Station_ptr, const int NumOfFiles );
    int RadiationInstrumentsConverter(const QString& FilenameIn, QStringList& FilenameOut, structMethod *Method_ptr, structStation *Station_ptr, const int NumOfFiles );
    int AssignmentConverter(const QString& FilenameIn, QStringList& FilenameOut, structMethod *Method_ptr, structStation *Station_ptr, const int NumOfFiles );
    int CreateReferenceImportFile(const QString& FilenameIn, QStringList& FilenameOut, structStaff *Staff_ptr, structStation *Station_ptr, const int NumOfFiles );

// Data
    int BasicMeasurementsTest( const QString& FilenameIn, int *P, const int NumOfFiles );
    int BasicMeasurementsConverter( const bool Import, const QString& FilenameIn, structParameter *Parameter_0001, structParameter *Parameter_0009, structMethod *Method_ptr, structStaff *Staff_ptr, structStation *Station_ptr, const bool overwriteDataset, structDataset *Dataset_ptr, const int NumOfFiles );
    int OtherMinuteMeasurementsConverter( const bool Import, const QString& FilenameIn, structStaff *Staff_ptr, structStation *Station_ptr, int *P, const int NumOfFiles );
    int UltraVioletMeasurementsTest( const QString& FilenameIn, int *P, const int NumOfFiles );
    int UltraVioletMeasurementsConverter( const bool Import, const QString& FilenameIn, structParameter *Parameter_0001, structParameter *Parameter_0009, structMethod *Method_ptr, structStaff *Staff_ptr, structStation *Station_ptr, const bool overwriteDataset, structDataset *Dataset_ptr, const int NumOfFiles );
    int SYNOPTest( const QString& FilenameIn, int *P, const int NumOfFiles );
    int SYNOPConverter( const bool Import, const QString& FilenameIn, structStaff *Staff_ptr, structStation *Station_ptr, const bool overwriteDataset, structDataset *Dataset_ptr, const int NumOfFiles );
    int RadiosondeMeasurementsTest( const QString& FilenameIn, int *P, const int NumOfFiles );
    int RadiosondeMeasurementsConverter( const bool Import, const QString& FilenameIn, structMethod *Method_ptr, structStaff *Staff_ptr, structStation *Station_ptr, const bool overwriteDataset, structDataset *Dataset_ptr, const int NumOfFiles );
    int OzoneMeasurementsConverter( const bool Import, const QString& FilenameIn, structMethod *Method_ptr, structStaff *Staff_ptr, structStation *Station_ptr, const bool overwriteDataset, structDataset *Dataset_ptr, const int NumOfFiles );
    int ExpandedMeasurementsTest( const QString& FilenameIn, int *P, const int NumOfFiles );
    int ExpandedMeasurementsConverter( const bool Import, const QString& FilenameIn, structMethod *Method_ptr, structStaff *Staff_ptr, structStation *Station_ptr, const bool overwriteDataset, structDataset *Dataset_ptr, const int NumOfFiles );
    int OtherMeasurementsAtXmTest( const QString& FilenameIn, int *P, const int Height, const int NumOfFiles );
    int OtherMeasurementsAtXmConverter( const bool Import, const QString& FilenameIn, const int Height, structParameter *Parameter_0001, structParameter *Parameter_0009, structMethod *Method_ptr, structStaff *Staff_ptr, structStation *Station_ptr, const bool overwriteDataset, structDataset *Dataset_ptr, const int i_NumOfFiles );

// Dialogs
    int doConcatenateOptionsDialog( int &SkipNFirstLines, bool &deleteOriginalFiles );
    int doDownloadManagerDialog( QString &DownloadPath, QString &FTPServer, QString &User, QString &Password, bool &DecompressFiles, bool &CheckFiles, bool &CheckAvailability, bool Station[MAX_NUM_OF_STATION+1], bool Month[MAX_NUM_OF_MONTH+1], bool Year[MAX_NUM_OF_YEAR+1] );
    int doQualityCheckRecommendedV20OptionsDialog(bool & b_CheckPhysicallyPossibleLimits, bool & b_CheckExtremelyRareLimits, bool & b_CheckComparisons, QString & s_AuxiliaryDataAlgorithm, bool & b_OutputCodes, bool & b_OutputCleanedValues, bool & b_OutputOriginalValues, bool & b_OutputAuxiliaryData, bool & b_OutputOneFile);
    int doFormatUnformattedOptionsDialog( QString &MissingValue, int &FieldDelimiter );
    int doFormatFormattedOptionsDialog( int &FieldAlignment, int &FieldWidth, QString &MissingValue );

// Tools
    QString ReferenceOtherVersionClassic( const QString& s_EventLabel, const QDateTime dt );
    QString ReferenceOtherVersion(const QString& EventLabel, const QDateTime dt );
    QString ReferenceImportFile(const QString& EventLabel, const QDateTime dt , const int PIID, const QString &StationName );

    QString OpenDataDescriptionHeader();
    QString CloseDataDescriptionHeader();
    QString DataSetID( const int DatasetID );
    QString DataSetID(const QString& Text = "" );
    QString AuthorIDs( const int PIID );
    QString SourceID( const int SourceID );
    QString Title( const QString& Text, const QString& StationName, const QDateTime dt );
    QString ExportFilename(const QString& EventLabel, const QString& Text, const QDateTime dt );
    QString EventLabel( const QString& EventLabel );
    QString Parameter( const int ParameterID, const int PIID = 506, const int MethodID = 43, const QString& Format = "", const QString& Comment = "" );
    QString ParameterFirst( const int ParameterID, const int PIID = 506, const int MethodID = 43, const QString& Format = "", const QString& Comment = "" );
    QString ParameterLast( const int ParameterID, const int PIID = 506, const int MethodID = 43, const QString& Format = "", const QString& Comment = "" );
    QString DatasetComment( const QString& Comment );
    QString ProjectIDs( const int ProjectID );
    QString TopologicTypeID( const int TopologicTypeID );
    QString StatusID( const int StatusID );
    QString UserIDs( const int UserID );
    QString LoginID( const int LoginID );

    QString findEventLabel( const int StationNumber, structStation *Station_ptr );
    QString findStationName( const int StationNumber, structStation *Station_ptr );
    bool checkFilename( const QString& s_Filename, const QString& s_EventLabel, const QString& s_Month, const QString& s_Year );

    int findInstituteID( const int StationNumber, structStation *Station_ptr );
    int findPiId( const QString& Name, structStaff *Staff_ptr );
    int findMethodID( const int StationNumber, const int WRMCnumber, structMethod *Method_ptr );
    int findMethodID( const QString& RadiosondeIdentification, structMethod *Method_ptr );
    int findDatasetId( const QString& ExportFilename, structDataset *Dataset_ptr );

    int readIDs();
    int writeDefaultIDs( const QString& Filename );

    int concatenateFiles( const QString& FilenameOut, const QStringList Filenames, const QString& ProgressMessage, const int SkipLines = 0, const bool RemoveFile = false );
    int convertEOL( const QString& FilenameIn, const bool convertEOL, const int OS );
    int convertFile( const QString& FilenameIn, const QString& FilenameOut, const QString& MissingValue, const int FieldDelimiter, const int NumOfFiles  );
    int convertFile( const QString& FilenameIn, const QString& FilenameOut, const int FieldAlignment, const int FieldWidth, const QString& MissingValue, const int NumOfFiles  );

    float calcGeopotentialHeight( const QString& ahhh );

//  Quality check
    int QualityCheckRecommendedV20(const QString & FileNameIn, const bool & b_CheckPhysicallyPossibleLimits, const bool & b_CheckExtremelyRareLimits, const bool & b_CheckComparisons, const QString & s_AuxiliaryDataAlgorithm, const bool & b_OutputCodes, const bool & b_OutputCleanedValues, const bool & b_OutputOriginalValues, const bool & b_OutputAuxiliaryData, const bool & b_OutputOneFile);
    //int QualityCheckTechnicalReport1( const QString& FilenameIn );
    //int QualityCheckUserDefined( const QString& FilenameIn );

    QMenu	*fileMenu;
    QMenu	*stationMenu;
    QMenu	*metadataMenu;
    QMenu	*dataMenu;
    QMenu	*importMenu;
    QMenu	*toolsMenu;
    QMenu   *qualityMenu;
    QMenu	*helpMenu;

    QAction *newWindowAction;
    QAction *openFileAction;
    QAction *openFolderAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *hideWindowAction;
    QAction *exitAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *helpAction;

    QAction *downloadStationToArchiveFilesAction;
    QAction *checkStationToArchiveFilesAction;

    QAction *doAllMetadataAction;
    QAction *fileIDAction;
    QAction *scientistIDAction;
    QAction *messagesAction;
    QAction *stationDescriptionAction;
    QAction *radiosondeEquipmentAction;
    QAction *ozoneEquipmentAction;
    QAction *stationHistoryAction;
    QAction *radiationInstrumentsAction;
    QAction *assignmentAction;
    QAction *createRefFileAction;

    QAction *doAllDataAction;
    QAction *basicMeasurementsAction;
    QAction *otherMinuteMeasurementsAction;
    QAction *uvMeasurementsAction;
    QAction *synopAction;
    QAction *radiosondeMeasurementsAction;
    QAction *ozoneMeasurementsAction;
    QAction *expandedMeasurementsAction;
    QAction *otherMeasurementsAt10mAction;
    QAction *otherMeasurementsAt30mAction;
    QAction *otherMeasurementsAt300mAction;

    QAction *doAllImportAction;
    QAction *basicMeasurementsImportAction;
    QAction *uvMeasurementsImportAction;
    QAction *synopImportAction;
    QAction *radiosondeMeasurementsImportAction;
    QAction *ozoneMeasurementsImportAction;
    QAction *expandedMeasurementsImportAction;
    QAction *otherMeasurementsAt10mImportAction;
    QAction *otherMeasurementsAt30mImportAction;
    QAction *otherMeasurementsAt300mImportAction;
    QAction *setOverwriteDatasetFlagAction;

    QAction *convertUnformattedAction;
    QAction *convertFormattedAction;
    QAction *concatenateFilesAction;
    QAction *WinConvertEOLAction;
    QAction *MacOSConvertEOLAction;
    QAction *compressFileAction;

    QAction *QualityCheckRecommendedV20Action;

    QPointer<QProgressDialog> ProgressDialog;
    QPointer<QProgressDialog> FileProgressDialog;
    QPointer<QProgressBar>    ProgressBar;

    QErrorMessage       *ErrorMessage;
    QLabel              *StatusMessage;

    QStringListModel	*Model;
    QListView			*ListView;

    QTextEdit			*textViewer;

    QPoint	posWindow;	//!< Position des Programmfensters.
    QSize	sizeWindow;	//!< Groesse des Programmfensters.

    QPoint  posDialog;  //!< Position der Dialoge

    structStation	*g_Station_ptr;
    structStaff		*g_Staff_ptr;
    structMethod	*g_Method_ptr;
    structDataset	*g_Dataset_ptr;
};

#endif
