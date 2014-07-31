/*
 * Main Function
 * Author: ShervinKH145
 * Date: 1391/2/17
 * Version: 1.1
 * License:
 *  This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Sudoku_Solver.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char*argv[])
{
	QApplication app(argc, argv);

	Sudoku_Solver SS;
	SS.widget()->show();
	app.setWindowIcon(QIcon(":/App.png"));
	SS.widget()->setWindowTitle("Sudoku Solver By Leo145");
	
	#ifdef Q_OS_WIN32
	SS.widget()->setBackgroundRole(QPalette::Dark);
	SS.widget()->setAutoFillBackground(true);
	#endif

	return app.exec();
}
