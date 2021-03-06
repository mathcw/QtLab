#include <QApplication>
#include <QLineEdit>
#include <QDragEnterEvent>
#include <QFileInfo>
#include <QMimeData>

class FileEdit : public QLineEdit {
public:
	FileEdit(QWidget *parent = nullptr) : QLineEdit(parent)
	{
		setAcceptDrops(true);
	}

protected:
	virtual void dragEnterEvent ( QDragEnterEvent * event ) override
	{
		if (event->mimeData()->hasUrls())
			event->acceptProposedAction();
	}

	virtual void dragMoveEvent(QDragMoveEvent * event) override
	{
		if (event->mimeData()->hasUrls())
			event->acceptProposedAction();
	}

	virtual void dropEvent(QDropEvent * event) override
	{
		if (event->mimeData()->hasUrls())
		{
			QList<QUrl> list = event->mimeData()->urls();
			QFileInfo * fileInfo = new QFileInfo(list.at(0).toLocalFile());
			setText(fileInfo->absoluteFilePath());
			event->acceptProposedAction();
		}
	}
};

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	FileEdit editor;
	editor.show();
	return app.exec();
}
