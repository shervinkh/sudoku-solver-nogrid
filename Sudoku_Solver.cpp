/*
 * Sudoku Solver Class Implementation
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

#include <QtGui>
#include "Sudoku_Solver.h"
#include <algorithm>
#include <ctime>

Sudoku_Solver::Sudoku_Solver()
{
	//Set Title Box - Start
	title = new QLabel("Sudoku Solver");

	QFont font;
	font.setBold(true);
	font.setPointSize(20);
	font.setWeight(75);
	title->setFont(font);

	horizontalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	horizontalSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

	titleBox = new QHBoxLayout;
	titleBox->addItem(horizontalSpacer1);
	titleBox->addWidget(title);
	titleBox->addItem(horizontalSpacer2);
	//Set Title Box - End

	//Set Grid - Start
	QRegExp regExp("[1-9]{0,1}");

	grid = new QGridLayout;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			grid->addWidget(&le[i][j],i,j,1,1);
			le[i][j].setValidator(new QRegExpValidator(regExp));
			le[i][j].setMinimumSize(QSize(25,22));
			le[i][j].setMaximumSize(QSize(25,22));
			le[i][j].setBaseSize(QSize(25,22));
			connect(&le[i][j], SIGNAL(textChanged(const QString &)), this, SLOT(setTable(const QString &)));
		}
	grid->setGeometry(QRect(1,1,10,10));
	//Set Grid - End

	//Set Solve Box - Start
	horizontalSpacer3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	horizontalSpacer4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	horizontalSpacer8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	solveButton = new QPushButton("Solve");

	QFont font2;
	font2.setBold(true);
	font2.setPointSize(18);
	font2.setWeight(75);
	solveButton->setFont(font2);

	resetButton = new QPushButton("Reset");
	resetButton->setFont(font2);

	solveBox = new QHBoxLayout;
	solveBox->addItem(horizontalSpacer3);
	solveBox->addWidget(solveButton);
	solveBox->addItem(horizontalSpacer8);
	solveBox->addWidget(resetButton);
	solveBox->addItem(horizontalSpacer4);
	//Set Solve Box - End

	//Set Status Box - Start
	horizontalSpacer5= new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	horizontalSpacer6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	horizontalSpacer7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

	status = new QLabel("Status: ");
	status->setFont(font2);

	stat = new QLabel("<html><head/><body><p><span style=\" color:#c05800;\">Pending</span></p></body></html>");
	stat->setFont(font2);

	statusBox = new QHBoxLayout;
	statusBox->addItem(horizontalSpacer5);
	statusBox->addWidget(status);
	statusBox->addItem(horizontalSpacer6);
	statusBox->addWidget(stat);
	statusBox->addItem(horizontalSpacer7);
	//Set Status Box - End

	//Set Whole Widget - Start
	total = new QVBoxLayout;
	total->addLayout(titleBox);
	total->addLayout(grid);
	total->addLayout(solveBox);
	total->addLayout(statusBox);
	total->setSizeConstraint(QLayout::SetFixedSize);

	wid = new QWidget;
	wid->setLayout(total);
	//Set Whole Widget - End 

	//Solve Button
	connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));
	connect(solveButton, SIGNAL(clicked()), this, SLOT(SolvePuzzle()));

	//Initialize Table
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			table[i][j] = 0;

	//Seed Random Function
	std::srand(std::time(0));
}

void Sudoku_Solver::setTable(const QString &str)
{
	stat->setText("<html><head/><body><p><span style=\" color:#c05800;\">Pending</span></p></body></html>");
	QLineEdit *point = qobject_cast<QLineEdit *>(sender());
	int x = (point - &le[0][0])/9;
	int y = (point - &le[0][0])%9;

	if (str.isEmpty())
		table[x][y] = 0;
	else
		table[x][y] = str.toInt();
}

void Sudoku_Solver::SolvePuzzle()
{
	stat->setText("<html><head/><body><p><span style=\" color:#0000c0;\">Processing</span></p></body></html>");
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			blacklist_row[i][j] = blacklist_col[i][j] = false;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 9; k++)
				blacklist_squ[i][j][k] = false;

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (table[i][j])
			{
				int cur = table[i][j];
				cur--;

				if (blacklist_row[i][cur] || blacklist_col[j][cur] || blacklist_squ[i/3][j/3][cur])
				{
					stat->setText("<html><head/><body><p><span style=\" color:#c00000;\">No Solution</span></p></body></html>");
					return;
				}

				blacklist_row[i][cur] = blacklist_col[j][cur] = blacklist_squ[i/3][j/3][cur] = true;
			}


	if (Solve(0,0))
	{
		updateGrid();
		stat->setText("<html><head/><body><p><span style=\" color:#008000;\">Solved</span></p></body></html>");
	}
	else
		stat->setText("<html><head/><body><p><span style=\" color:#c00000;\">No Solution</span></p></body></html>");
}

void Sudoku_Solver::updateGrid()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			le[i][j].setText(QString::number(table[i][j]));
}

bool Sudoku_Solver::Solve(int x, int y)
{
	quint8 temp_ar[9];
	if (y == 9)
	{
		y = 0;
		x++;
	}

	if (x == 9)
		return true;

	if (table[x][y] != 0)
		return Solve(x,y+1);

	int count = 0;
	for (int i = 0; i < 9; i++)
		if (!blacklist_row[x][i] && !blacklist_col[y][i] && !blacklist_squ[x/3][y/3][i])
			temp_ar[count++] = i+1;

	std::random_shuffle(temp_ar,temp_ar+count);

	for (int i = 0; i < count; i++)
	{
		blacklist_row[x][temp_ar[i]-1] = blacklist_col[y][temp_ar[i]-1] = blacklist_squ[x/3][y/3][temp_ar[i]-1] = true;
		table[x][y] = temp_ar[i];
		if (Solve(x,y+1))
			return true;
		table[x][y] = 0;
		blacklist_row[x][temp_ar[i]-1] = blacklist_col[y][temp_ar[i]-1] = blacklist_squ[x/3][y/3][temp_ar[i]-1] = false;  
	}
	return false;
}

void Sudoku_Solver::reset()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			le[i][j].setText("");
}
