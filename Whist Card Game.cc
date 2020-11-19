//********************************************************************************************//
// Whist Card Game
// AmirKabir University of Technology-Tehran Polytechnic
// C++ Course Final Project December 2014
// Github: Forouzanfallah1
// Personal Website: Forouzanfallah.ir
// don't hesitate to contact me for any further questions
//********************************************************************************************//

#include <iostream>
#include <ctime>
#include <conio.h>
#include <cstdlib>
using namespace std;

void print(int ,int);
void sort(int[], int);
int human_player(int[],int);

int main()
{
	//define all variables
	int player[4][13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int team1_score = 0;
	int team2_score = 0;
	int card_type;
	int compare_card[4];
	int winner_card;
	int lead = 0;
	int leader = 0;
	int all_card[52] = {  101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113
						, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213
						, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313
						, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413};

	srand(time(0));

	// shuffling and dealing
	for (int i,j, counter = 0; counter <= 2000; counter++)
	{
		int hold;
		j = floor((rand() /32767.00)*52);
		i = floor((rand() / 32767.00) * 52);
		hold = all_card[j];
		all_card[j] = all_card[i];
		all_card[i] = hold;
	}



	//	Choosing leader

	for (int counter = 0; counter <= 51; counter++)
	{
		if (all_card[counter] % 100 == 13)
		{
			leader = counter % 4;
			break;
		}
	}


	//first time: Give 5 cards to leader!
	for (int counter = 0; counter <= 4; counter++)
		player[leader][counter] = all_card[counter];

	int lead_card[4] = { 0, 0, 0, 0 };
	switch (leader)
	{
	case 0:	cout << "leader : Me" << endl;
		break;
	case 1:cout << "leader : Player 2" << endl;
		break;
	case 2:cout << "leader : Player 3" << endl;
		break;
	case 3:cout << "leader : Player 4" << endl;
	}

	if (leader == 0)						//choosing lead
	{
		int j = 0;
		int human_lead[5] = { player[0][0], player[0][1], player[0][2], player[0][3], player[0][4]};
		int a;
		sort(human_lead, 5);

		for (int i = 0; i <= 4; i++)
		{
			int a = 0;
					switch (player[0][i] % 100)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				{
					cout << i+1 << ") " << (player[0][i] % 100 + 1) << char(player[0][i] / 100 + 2) << "\t";
					break;
				}
				case 10:
				{
					cout << i +1<< ") " << "J" << char(player[0][i] / 100 + 2) << "\t";
					break;
				}
				case 11:
				{
					cout << i+1 << ") " << "Q" << char(player[0][i] / 100 + 2) << "\t";
					break;
				}
				case 12:
				{
					cout << i+1 << ") " << "K" << char(player[0][i] / 100 + 2) << "\t";
					break;
				}
				case 13:
				{
					cout << i+1 << ") " << "A" << char(player[0][i] / 100 + 2) << "\t";
					break;
				}
			}
		}
		cout << endl;

		cout << "Choose your lead : ";
		for (int i=0 ; i<=3 ; i++)
		{
			cout << i+1<<") "<<char(i+3) << "\t";
		}
		cout<<endl;
		cin >> a;
		lead = a;
		system("cls");
	}


	else
	{

		for (int i = 0; i <= 4; i++)
		{
			switch (player[leader][i] / 100)
			{
			case 1: lead_card[0] = lead_card[0] + player[leader][i] % 100;
				break;
			case 2: lead_card[1] = lead_card[1] + player[leader][i] % 100;
				break;
			case 3: lead_card[2] = lead_card[2] + player[leader][i] % 100;
				break;
			case 4: lead_card[3] = lead_card[3] + player[leader][i] % 100;
			}

		}

		int max = 0;
		for (int counter = 0; counter <=3 ; counter++)
		{
			if(max < lead_card[counter])
				max = lead_card[counter];
		}

		for(int counter = 0; counter<=3 ; counter++)
		{
			if (lead_card[counter]== max)
			{
				lead = counter+1;
			break;
			}
		}
	}

	// Give 5 cards to other players!

	for (int counter = 0; counter <= 4; counter++)
		player[(leader + 1) % 4][counter] = all_card[counter + 5];

	for (int counter = 0; counter <= 4; counter++)
		player[(leader + 2) % 4][counter] = all_card[counter +10];

	for (int counter = 0; counter <= 4; counter++)
		player[(leader + 3) % 4][counter] = all_card[counter + 15];
	//---------------------------------------------------------------

	// Give 8 cards to all player

	for (int counter = 0; counter <= 7; counter++)
		player[leader][counter+5] = all_card[counter + 20];

	for (int counter = 0; counter <= 7; counter++)
		player[(leader + 1) % 4][counter+5] = all_card[counter + 28];

	for (int counter = 0; counter <= 7; counter++)
		player[(leader + 2) % 4][counter+5] = all_card[counter + 36];

	for (int counter = 0; counter <= 7; counter++)
		player[(leader + 3) % 4][counter+5] = all_card[counter + 44];

	//Sort player cards

	sort(player[0], 13);
	sort(player[1], 13);
	sort(player[2], 13);
	sort(player[3], 13);


	//	Players deside to choose a card!

	int turn = leader;
	int recycle_bin[52] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int recycle_bin_counter = 0;
	int card[4] = { 0, 0, 0, 0 };
	for (int wave = 1; wave <= 13; wave++) // Round counter
	{
		int hold1 = 0;
		hold1 = 0;
		card[0] = 0, card[1] = 0, card[2] = 0, card[3] = 0;

		switch (lead)
		{
		case 1: cout << "lead is : " << char(lead + 2) << endl;
			break;
		case 2: cout << "lead is : " << char(lead + 2) << endl;
			break;
		case 3: cout << "lead is : " << char(lead + 2) << endl;
			break;
		case 4: cout << "lead is : " << char(lead + 2) << endl;
			break;
		}

		cout << "Team 1 score =" << team1_score << "\t" << "\t" << "Team 2 score = " << team2_score << endl<<endl;
		card_type = 0;
		// First card!

		if (turn == 0)							//Human player
			card[turn % 4] = human_player(player[0], card_type);

		else
		{
			int j = floor(rand() / 32767.00 * 13); 	 // random 0..12
			while (player[turn % 4][j] == 0)
			{
				j = floor(rand() / 32767.00 * 13);
			}
			card[turn % 4] = player[turn % 4][j];
			player[turn % 4][j] = 0;		// remove card0 form player0 list cards!
		}

		hold1 = card[turn % 4];
		card_type = card[turn % 4] / 100;
		recycle_bin[recycle_bin_counter] = card[turn% 4];	// send card to the recycle bin list
		recycle_bin_counter++;

		for (int i = 0; i <= 12; i++)		//Card eraser!
		{
			if (card[turn % 4] == player[turn % 4][i])
			{
				player[turn  % 4][i] = 0;
				break;
			}
		}

		print(card[turn % 4], (turn % 4) );		//Print card

		if (card[turn % 4] / 100 == lead)
			card[turn % 4] = card[turn % 4] + 1000;



		// 2nd card!

		bool card_type_exist = false;
		int max = 0;
		int min = 2000; // greater than all number!
		int flag = 0;
		int hold2 = 0;
		hold2 = 0;

		for (int i = 0; i <= 12; i++)					//Card type exist checker!
		{
			if (player[(turn + 1) % 4][i] / 100 == card_type)
			{
				card_type_exist = true;
				break;
			}
		}

		if ((turn + 1) % 4 == 0)				//Human player!
			hold2 = human_player(player[0], card_type);
		else
		{
			if (card_type_exist == true)
			{
				for (int i = 0; i <= 12; i++)		// Choose maximum card number of card type!
				{
					if (player[(turn + 1) % 4][i] > max  &&  player[(turn + 1) % 4][i] / 100 == card_type)
					{
						max = player[(turn + 1) % 4][i];
					}
				}

				int max_counter = 0;		//counter of how many card in recycle bin greater than max card!
				for (int i = 0; i <= 51; i++)
				{
					if ((max < recycle_bin[i] && recycle_bin[i] / 100 == card_type) || max % 100 == 13)		//checking that greater cards of max card are existance or not!
					{
						max_counter++;
						if ( max_counter == 13 - (max - (card_type * 100)) || max_counter == 13 - (max - (card_type * 100)) -1  || max % 100 == 13)
						{
							flag = 1;
							break;
						}
					}
				}


				if (flag == 1 && max > hold1)
					hold2 = max;


				else       // else choose minimum card!
				{
					for (int i = 0; i <= 12; i++)
					{
						if (min > player[(turn + 1) % 4][i] && player[(turn + 1) % 4][i] / 100 == card_type)
						{
							min = player[(turn + 1) % 4][i];
						}
					}
					hold2 = min;

				}
			}

			//If player haven't any cards of card type...


			if (card_type_exist == false)
			{
				min = 2000;
				for (int i = 0; i <= 12; i++)		// Choose minimum lead card!
				{
					if (player[(turn + 1) % 4][i] < min && player[(turn + 1) % 4][i] / 100 == lead)
						min = player[(turn + 1) % 4][i];
				}
				if (min + 1000 > card[turn%4])
				hold2 = min;

				//If player wants to ignore a card



				if (hold2 == 0	|| hold2 ==2000)
				{
					int min_card_num = 14;
					min = 2000;

					for (int i = 0; i <= 12; i++)
					{
						if (player[(turn + 1) % 4][i] % 100 < min_card_num  &&  player[(turn + 1) % 4][i] / 100 != lead && player[(turn + 1) % 4][i] != 0)
						{
							min = player[(turn + 1) % 4][i];
							min_card_num = min % 100;
						}
					}
					hold2 = min;
				}


				if (hold2 == 0	|| hold2 ==2000)				//if he haven't cards execpt lead cards,he have to ignore a lead card
				{
					for (int i = 0; i <= 12; i++)
					{
						if (player[(turn + 1) % 4][i] != 0)
						{
							hold2 = player[(turn + 1) % 4][i];
							break;
						}
					}
				}


			}
		}

		card[(turn + 1) % 4] = hold2;
		recycle_bin[recycle_bin_counter] = card[(turn + 1) % 4];	// send card to the recycle bin list
		recycle_bin_counter++;

		for (int i = 0; i <= 12; i++)		//Card eraser
		{
			if (card[(turn + 1) % 4] == player[(turn + 1) % 4][i])
			{
				player[(turn + 1) % 4][i] = 0;
				break;
			}
		}

		print(card[((turn + 1) % 4)], ((turn + 1) % 4) );		// Print card!

		if (card[(turn + 1) % 4] / 100 != lead)
		{
			if (card[(turn + 1) % 4] / 100 != card_type)
				card[(turn + 1) % 4] = 0;
		}

		if (card[(turn + 1) % 4] / 100 == lead)
			card[(turn + 1) % 4] = card[(turn + 1) % 4] + 1000;


		// 3rd card!

		card_type_exist = false;
		int hold3 =0;
		hold3 = 0;
		bool win = false;
		min = 2000;
		max = 0;
		flag = 0;

		if ( ((turn+2) % 4)== 0)
			hold3 = human_player(player[0], card_type);
		else
		{
			for (int i = 0; i <= 12; i++)					//Card type exist checker!
			{
				if (player[(turn + 2) % 4][i] / 100 == card_type)
				{
					card_type_exist = true;
					break;
				}
			}
			//-----------------------------

			if (card[turn % 4] > card[(turn+1) % 4])			// If player team win before... , he should choose minimum card!
			{
				if (card[turn % 4] % 100 == 13 || card[turn % 4] % 100 == 12 || card[turn % 4] % 100 == 11 || card[turn % 4] % 100 == 10)
				{

					if (card_type_exist == true)			//If he have cards of card type, choose minimum card of card type!
					{
						for (int i = 0; i <= 12; i++)
						{
							if (min > player[(turn + 2) % 4][i] && player[(turn + 2) % 4][i] / 100 == card_type)
							{
								min = player[(turn + 2) % 4][i];
							}
						}
						hold3 = min;
					}

					else
					{
						int min_card_num = 14;
						min = 2000;
						for (int i = 0; i <= 12; i++)
						{
							if (player[(turn + 2) % 4][i] % 100 < min_card_num  &&  player[(turn + 2) % 4][i] / 100 != lead && player[(turn + 2) % 4][i] != 0)
							{
								min = player[(turn + 2) % 4][i];
								min_card_num = min % 100;
							}
						}
						hold3 = min;
					}

					if (hold3 == 0 || hold3 == 2000)				//if he haven't cards execpt lead cards,he have to ignore a lead card
					{
						for (int i = 0; i <= 12; i++)
						{
							if (player[(turn + 2) % 4][i] != 0)
							{
								hold3 = player[(turn + 2) % 4][i];
								break;
							}
						}
					}
				}

				else         //his team win, but not with a great card!
				{
					if (card_type_exist == true)		// Choose maximum card number of card type!
					{
						max = 0;
						for (int i = 0; i <= 12; i++)
						{
							if (player[(turn + 2) % 4][i] > max  &&  player[(turn + 2) % 4][i] / 100 == card_type)
							{
								max = player[(turn + 2) % 4][i];
							}

							if (max > hold1 && max > hold2)
								hold3 = max;
						}

						if (hold3 == 0	|| hold3 == 2000)				//// Choose minimum card number of card type!
						{
							min = 2000;
							for (int i = 0; i <= 12; i++)
							{
								if (min > player[(turn + 2) % 4][i] && player[(turn + 2) % 4][i] / 100 == card_type)
								{
									min = player[(turn + 2) % 4][i];
								}
							}
							hold3 = min;
						}
					}

					else          // card_type_exist =false
					{

						int min_card_num = 14;
						min = 2000;

						for (int i = 0; i <= 12; i++)					// Choose minimum cards of other card types
						{
							if (player[(turn + 2) % 4][i] > hold1 && player[(turn + 2) % 4][i] > hold2 && player[(turn + 2) % 4][i] / 100 == lead)
							{
								hold3 = player[(turn + 2) % 4][i];
								break;
							}
						}

						if (hold3 == 0	|| hold3 == 2000)						//Choose a minimum card!
						{
							for (int i = 0; i <= 12; i++)
							{
								if (player[(turn + 2) % 4][i] % 100 < min_card_num  &&  player[(turn + 2) % 4][i] / 100 != lead && player[(turn + 2) % 4][i] != 0)
								{
									min = player[(turn + 2) % 4][i];
									min_card_num = min % 100;
								}
							}
							hold3 = min;
						}

						if (hold3 == 0	|| hold3 == 2000)				//if he haven't cards execpt lead cards,he have to ignore a lead card!
						{
							for (int i = 0; i <= 12; i++)
							{
								if (player[(turn + 2) % 4][i] != 0)
								{
									hold3 = player[(turn + 2) % 4][i];
									break;
								}
							}
						}


					}
				}
			}

			else           //Card[1st] < Card[2nd]  if they lost..
			{

				if (card_type_exist == true)
				{
					for (int i = 0; i <= 12; i++)		// Choose maximum card number of card type!
					{
						if (player[(turn + 2) % 4][i] > max  &&  player[(turn + 2) % 4][i] / 100 == card_type)
							max = player[(turn + 2) % 4][i];
					}

					if (max > hold2 && max > hold1)
						hold3 = max;


					if (hold3 == 0)       // else choose minimum card of card type!
					{
						for (int i = 0; i <= 12; i++)
						{
							if (min > player[(turn + 2) % 4][i] && player[(turn + 2) % 4][i] / 100 == card_type)
							{
								min = player[(turn + 2) % 4][i];
							}
						}
						hold3 = min;
					}
				}

				if (card_type_exist == false)
				{
					min = 2000;
					for (int i = 0; i <= 12; i++)		//If player haven't any cards of card type, he should choose a lead card!
					{
						if (player[(turn + 2) % 4][i] < min && player[(turn + 2) % 4][i] / 100 == lead)
						{
							min = player[(turn + 2) % 4][i];
							break;
						}
						if (min + 1000 > card[(turn + 1)%4])
						hold3 = min;
					}

					if (hold3 == 0 || hold3 == 2000)		//player haven't any lead card, he should ignore a minimum value card!
					{

						int min_card_num = 14;
						min = 2000;

						for (int i = 0; i <= 12; i++)
						{
							if (player[(turn + 2) % 4][i] % 100 < min_card_num  &&  player[(turn + 2) % 4][i] / 100 != lead && player[(turn + 2) % 4][i] != 0)
							{
								min = player[(turn + 2) % 4][i];
								min_card_num = min % 100;
							}
							hold3 = min;
						}



						if (hold3 == 0 || hold3 == 2000)			//if he haven't cards execpt lead cards,he have to ignore a lead card!
						{
							for (int i = 0; i <= 12; i++)
							{
								if (player[(turn + 2) % 4][i] != 0)
								{
									hold3 = player[(turn + 2) % 4][i];
									break;
								}
							}
						}

					}
				}
			}
		}

		card[(turn + 2) % 4] = hold3;
		recycle_bin[recycle_bin_counter] = card[(turn + 2) % 4];	// send card to the recycle bin list
		recycle_bin_counter++;

		for (int i = 0; i <= 12; i++)		//Card eraser!
		{
			if (card[(turn + 2) % 4] == player[(turn + 2) % 4][i])
			{
				player[(turn + 2) % 4][i] = 0;
				break;
			}
		}

		print(card[((turn + 2) % 4)], ((turn + 2) % 4));		// Print card!

		if (card[(turn + 2) % 4] / 100 != lead)
		{
			if (card[(turn + 2) % 4] / 100 != card_type)
				card[(turn + 2) % 4] = 0;
		}

		if (card[(turn + 2) % 4] / 100 == lead)
			card[(turn + 2) % 4] = card[(turn + 2) % 4] + 1000;



		// 4th card

		int hold4 = 0;
		hold4 = 0;
		card_type_exist = false;
		bool win_ability = false;
		win = false;

		if ((turn + 3) % 4 == 0)
			hold4 = human_player(player[0], card_type);
		else
		{
			for (int i = 0; i <= 12; i++)					//Card type exist checker!
			{
				if (player[(turn + 3) % 4][i] / 100 == card_type)
				{
					card_type_exist = true;
					break;
				}
			}

			if (card[turn%4] < card[(turn + 1) % 4] && card[(turn + 2) % 4] < card[(turn + 1) % 4])				//Checking that his team win at this time or not!
				win = true;

			for (int i = 0; i <= 12; i++)				//Checking that his team1 can win or not! (with card type)
			{
				if (player[(turn + 3) % 4][i] > hold1 && player[(turn + 3) % 4][i] > hold3 && card_type_exist == true && player[(turn + 3) % 4][i] / 100 == card_type)
				{
					win_ability = true;
					break;
				}
			}

			for (int i = 0; i <= 12; i++)				//Checking that his team1 can win or not! (with lead)
			{
				if (player[(turn + 3) % 4][i] > hold1 && player[(turn + 3) % 4][i] > hold3 && card_type_exist == false && player[(turn + 3) % 4][i] / 100 == lead )
				{
					win_ability = true;
					break;
				}
			}

			min = 2000;
			if (win == true)				//If his team win at this time, he should choose minimum value card
			{
				if (card_type_exist == true)			//If he have cards of card type
				{
					for (int i = 0; i <= 12; i++)
					{
						if (player[(turn + 3) % 4][i] < min && player[(turn + 3) % 4][i] / 100 == card_type)
						{
							min = player[(turn + 3) % 4][i];
							break;
						}
					}
					hold4 = min;
				}

				else                         ////If he haven't cards of card type, he should ignore a card (possibly shouldn't be lead!)
				{
					min = 2000;
					int min_card_num = 14;
					for (int i = 0; i <= 12; i++)	// if player haven't any lead card , he have to ignore a card!
					{
						if (player[(turn + 3) % 4][i] % 100 < min_card_num  &&  player[(turn + 3) % 4][i] / 100 != lead && player[(turn + 3) % 4][i] != 0)
						{
							min = player[(turn + 3) % 4][i];
							min_card_num = min % 100;
						}
					}
				}
				hold4 = min;

				if (hold4 == 0	|| hold4 == 2000)				//if he haven't cards execpt lead cards,he have to ignore a lead card!
				{
					for (int i = 0; i <= 12; i++)
					{
						if (player[(turn + 3) % 4][i] != 0)
							hold4 = player[(turn + 3) % 4][i];
					}
				}
			}

			if (win == false && win_ability == true)		//If his team can win
			{
				if (card_type_exist == true)				//if he have cards of card type
				{
					for (int i = 0; i <= 12; i++)
					{
						if (player[(turn + 3) % 4][i] > hold1 && player[(turn + 3) % 4][i] > card[(turn+2)%4] && player[(turn + 3) % 4][i] / 100 == card_type)
						{
							hold4 = player[(turn + 3) % 4][i];
							break;
						}
					}
				}

				else                  ////if he haven't cards of card type,he should choose lead card!
				{
					for (int i = 0; i <= 12; i++)
					{
						if (player[(turn + 3) % 4][i] + 1000 > card[turn % 4] && player[(turn + 3) % 4][i] + 1000 > card[(turn+1) % 4] && player[(turn + 3) % 4][i] / 100 == lead)
						{
							hold4 = player[(turn + 3) % 4][i];
							break;
						}
					}
				}

			}

			if (win == false && win_ability == false)				//his team defeated and his team can't win, he should choose a minimum card value!
			{
				min = 2000;
				if (card_type_exist == true)			//If he have cards of card type
				{
					for (int i = 0; i <= 12; i++)
					{
						if (player[(turn + 3) % 4][i] < min && player[(turn + 3) % 4][i] / 100 == card_type)
						{
							min = player[(turn + 3) % 4][i];
							break;
						}
					}
					hold4 = min;
				}

				else                         ////If he haven't cards of card type, he should ignore a card (possibly shouldn't be lead!)
				{
					min = 2000;
					int min_card_num = 14;
					for (int i = 0; i <= 12; i++)	// if player haven't any lead card , he have to ignore a card!
					{
						if (player[(turn + 3) % 4][i] % 100 < min_card_num  && player[(turn + 3) % 4][i]!= 0 && player[(turn + 3) % 4][i] / 100 != lead)
						{
							min = player[(turn + 3) % 4][i];
							min_card_num = min % 100;
						}
					}
					hold4 = min;
				}

				if (hold4 == 0	|| hold4 == 2000)				//if he haven't cards execpt lead cards,he have to ignore a lead card!
				{
					for (int i = 0; i <= 12; i++)
					{
						if (player[(turn + 3) % 4][i] != 0)
						{
							hold4 = player[(turn + 3) % 4][i];
							break;
						}
					}
				}

			}
		}

		card[(turn + 3) % 4] = hold4;
		recycle_bin[recycle_bin_counter] = card[(turn + 3) % 4];	// send card to the recycle bin list
		recycle_bin_counter++;

		for (int i = 0; i <= 12; i++)		//Card eraser!
		{
			if (card[(turn + 3) % 4] == player[(turn + 3) % 4][i])
			{
				player[(turn + 3) % 4][i] = 0;
				break;
			}
		}

		print(card[((turn + 3) % 4)], ((turn + 3) % 4));		// Print card!

		if (card[(turn + 3) % 4] / 100 != lead)
		{
			if (card[(turn + 3) % 4] / 100 != card_type)
				card[(turn + 3) % 4] = 0;
		}

		if (card[(turn + 3) % 4] / 100 == lead)
			card[(turn + 3) % 4] = card[(turn + 3) % 4] + 1000;



		// Determine winner!

		compare_card[0] = card[(wave % 4)];
		compare_card[1] = card[((wave + 1) % 4)];
		compare_card[2] = card[((wave + 2) % 4)];
		compare_card[3] = card[((wave + 3) % 4)];

		sort(compare_card, 4);

		winner_card = compare_card[3];

		if (winner_card == card[0])
		{
			team1_score++;
			turn = 0;
		}
		else if (winner_card == card[2])
		{
			team1_score++;
			turn = 2;
		}

		if (winner_card == card[1])
		{
			team2_score++;
			turn = 1;
		}
		else if (winner_card == card[3])
		{
			team2_score++;
			turn = 3;
		}
		cout << "For the next round press any key!" << endl;
		_getch();
		system("cls");
		if (team1_score == 7)
		{
			cout << "Team 1 Win!" << endl;
			break;
		}
		else if (team2_score == 7)
		{
			cout << "Team 2 Win!!!!" << endl;
			break;
		}
	}

 	_getch();
	return 0;
}

//The End!


void print(int card , int player)
{
	int card_type;
	int num_card;
	int khal;
	player++;

	card_type = card / 100;
	num_card = card % 100;
	khal = card_type + 2;

	switch (player)
	{
	case 1: cout << "Me" << " : ";
		break;
	case 2: cout << "Player" << player << " : ";
		break;
	case 3: cout << "Player" << player << " : ";
		break;
	case 4: cout << "Player" << player << " : ";
	}

	switch (num_card)
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		{
			cout <<(num_card + 1) << char(khal) <<endl;
			break;
		}
		case 10:
		{
			cout <<"J" << char(khal)<<endl;
			break;
		}
		case 11:
		{
			cout <<"Q" << char(khal) << endl;
			break;
		}
		case 12:
		{
			cout <<"K" << char(khal) << endl;
			break;
		}
		case 13:
		{
			cout <<"A" << char(khal) << endl;
			break;
		}
	}

}


void sort(int Array[], int array_size)
{
	int flag = 1;
	int hold;
	while (flag == 1)
	{

		flag = 0;
		for (int i = 1; i < array_size; i++)
		{
			if (Array[i-1] > Array[i])
			{
				hold = Array[i];
				Array[i] = Array[i - 1];
				Array[i - 1] = hold;
				flag = 1;
			}
		}
	}
}



int human_player(int human[], int card_type)
{
	int counter = 0;
	cout << endl;

	bool card_type_exist = false;

	for (int i = 0; i <= 12; i++)
	{
		if (human[i] != 0)
		{
			counter++;
		}
	}

	int *human_card;			//Dynamic array!
	human_card = new int[counter];

	for (int i = 0, j =0; i <= 12; i++)
	{
		if (human[i] != 0)
		{
			j++;
			human_card[j] = human[i];
		}
	}



	for (int i = 0; i <= counter ; i++)
	{

		switch (human_card[i] % 100)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				{
					cout << i << ") " << (human_card[i] % 100 + 1) << char(human_card[i] / 100 + 2) << "\t";
					break;
				}
				case 10:
				{
					cout << i << ") " << "J" << char(human_card[i] / 100 + 2) << "\t";
					break;
				}
				case 11:
				{
					cout << i << ") " << "Q" << char(human_card[i] / 100 + 2) << "\t";
					break;
				}
				case 12:
				{
					cout << i << ") " << "K" << char(human_card[i] / 100 + 2) << "\t";
					break;
				}
				case 13:
				{
					cout << i << ") " << "A" << char(human_card[i] / 100 + 2) << "\t";
					break;
				}
			}

	}
	cout << endl;

	for (int i = 0; i < counter; i++)
	{
		if (human_card[i] / 100 == card_type || card_type == 0)
		{
			card_type_exist = true;
			break;
		}
	}

	int card_num = 1000;
	if (card_type_exist == true)
	{
		while (1>0)
		{
			cout << "Enter card number : " << endl;
			cin >> card_num;
			if (card_num > counter)
				cout << "Error" << endl;
			else
			{
				if (human_card[card_num] / 100 != card_type && card_type != 0 && card_num < 14)
					cout << "This card didn't match with card type!" << endl;
				else
					break;
			}

		}
		return human_card[card_num];
	}
	else
	{
		while (1 > 0)
		{
			cout << "Enter card number : "<< endl;
			cin >> card_num;
			if (card_num > counter)
				cout << "Error" << endl;
			else
				break;
		}
		return human_card[card_num];
	}
}
