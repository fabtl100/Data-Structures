#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define TILECOUNT 6

using namespace std;

// Count vertical and horizontal alignments in the board.
int CountAlignments(int **board, int boardSize)
{
    int j = 0, r = 0, count = 0;
    int alignmentCount = 0;
    // This loop counts the horizontal alignments.
    for(int i = 0; i < boardSize; i++)
    {
        count = 0;
        j = 0;
        r = 0;
        while((j + r) < boardSize)
        {
            // If the element to the right of i,j element is the same we increment the count.
            if(board[i][j] == board[i][j + r])
            {
                count++;
            }
            else
            {
                // When the element to the right is not the same we gotta check if when this line was reached
                // a count of more than 3 was reached. This means there is an alignment here to consider.
                if(count >= 3)
                {
                    alignmentCount++;
                }
                // This moves the iterator out of the already considered elements.
                j += count;
                count = 0;
                r = -1;
            }
            r++;
        }
        // This is when the exit condition has been met (j+r > boardSize)
        // we need to check if an alignment has been found when the condition was met.
        if(count >= 3)
        {
            alignmentCount++;
        }
    }
    // This loop counts the vertical alignments.
    for(int i = 0; i < boardSize; i++)
    {
        count = 0;
        j = 0;
        r = 0;
        while((j + r) < boardSize)
        {
            // If the element to the bottom of i,j element is the same we increment the count.
            if(board[j][i] == board[j + r][i])
            {
                count++;
            }
            else
            {
                // When the element to the bottom is not the same we gotta check if when this line was reached
                // a count of more than 3 was reached. This means there is an alignment here to consider.
                if(count >= 3)
                {
                    alignmentCount++;
                }
                // This moves the iterator out of the already considered elements.
                j += count;
                count = 0;
                r = -1;
            }
            r++;
        }
        // This is when the exit condition has been met (j+r > boardSize)
        // we need to check if an alignment has been found when the condition was met.
        if(count >= 3)
        {
            alignmentCount++;
        }
    }
    return alignmentCount;
}

// Show the board on console.
void Show(int **board, int boardSize)
{
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            if(board[i][j] < 10)
                cout<<board[i][j]<<"  ";
            else
                cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}

// Initialize the board with random numbers making sure no alignments are present in the board.
void Initialize(int **board, int boardSize)
{
    time_t t;
    // Feed the random seed with the pc's time so each time there's is a different set of numbers being considered.
    srand((unsigned) time(&t));
    // Get random numbers and put them in the board.
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            board[i][j] = rand() % TILECOUNT + 1;
        }
    }

    int j = 0, r = 0, count = 0, swapAux = 0, swapIndex = 0;
    int alignmentCount = 1;
    // Swap elements in the board until no alignments are present
    while(alignmentCount > 0)
    {
        // The procedure here is similar to the one in CountAlignments():
        // the elements that are the same are counted horizontally and vertically when adjacent to
        // each other. If an alignment is found then one of the elements in the alignemnt is chosen 
        // randomly and a new number is generated for that position.

        // This loop considers horizontal alignments.
        for(int i = 0; i < boardSize; i++)
        {
            count = 0;
            j = 0;
            r = 0;
            while((j + r) < boardSize)
            {
                // If the element to the right of i,j element is the same we increment the count.
                if(board[i][j] == board[i][j + r])
                {
                    count++;
                }
                else
                {
                    // When the element to the right is not the same we gotta check if when this line was reached
                    // a count of more than 3 was reached. This means there is an alignment here to consider.
                    if(count >= 3)
                    {
                        // If an alignment is found then one of the numbers in the alignment
                        // will be swaped for a random one.
                        for(int l = 0; l < count; l++)
                        {
                            // Get a random number in the interval of the alignment.
                            swapIndex = rand() % count + 1;
                            // Get the element to swap using this random index.
                            swapAux = board[i][j + count - swapIndex];
                            // Generate a random number to put in the position of the item to swap.
                            board[i][j + count - swapIndex] = rand() % TILECOUNT + 1;
                            // Keep generating new numbers until it is different from the one causing the alignment.
                            while(board[i][j + count - swapIndex] == swapAux)
                                board[i][j + count - swapIndex] = rand() % TILECOUNT + 1;
                        }
                    }
                    // This moves the iterator out of the already considered elements.
                    j += count;
                    count = 0;
                    r = -1;
                }
                r++;
            }
            // This is when the exit condition has been met (j+r > boardSize)
            // we need to check if an alignment has been found when the condition was met.
            if(count >= 3)
            {
                // If an alignment is found then one of the numbers in the alignment
                // will be swaped for a random one.
                for(int l = 0; l < count; l++)
                {
                    // Get a random number in the interval of the alignment.
                    swapIndex = rand() % count + 1;
                    // Get the element to swap using this random index.
                    swapAux = board[i][j + count - swapIndex];
                    // Generate a random number to put in the position of the item to swap.
                    board[i][j + count - swapIndex] = rand() % TILECOUNT + 1;
                    // Keep generating new numbers until it is different from the one causing the alignment.
                    while(board[i][j + count - swapIndex] == swapAux)
                        board[i][j + count - swapIndex] = rand() % TILECOUNT + 1;
                }
            }
        }
        // This loop considers vertical alignments.
        for(int i = 0; i < boardSize; i++)
        {
            count = 0;
            j = 0;
            r = 0;
            while((j + r) < boardSize)
            {
                // If the element to the bottom of i,j element is the same we increment the count.
                if(board[j][i] == board[j + r][i])
                {
                    count++;
                }
                else
                {
                    // When the element to the bottom is not the same we gotta check if when this line was reached
                    // a count of more than 3 was reached. This means there is an alignment here to consider.
                    if(count >= 3)
                    {
                        // If an alignment is found then one of the numbers in the alignment
                        // will be swaped for a random one.
                        for(int l = 0; l < count; l++)
                        {
                            // Get a random number in the interval of the alignment.
                            swapIndex = rand() % count + 1;
                            // Get the element to swap using this random index.
                            swapAux = board[j + count - swapIndex][i];
                            // Generate a random number to put in the position of the item to swap.
                            board[j + count - swapIndex][i] = rand() % TILECOUNT + 1;
                            // Keep generating new numbers until it is different from the one causing the alignment.
                            while(board[j + count - swapIndex][i] == swapAux)
                                board[j + count - swapIndex][i] = rand() % TILECOUNT + 1;
                        }
                    }
                    // This moves the iterator out of the already considered elements.
                    j += count;
                    count = 0;
                    r = -1;
                }
                r++;
            }
            // This is when the exit condition has been met (j+r > boardSize)
            // we need to check if an alignment has been found when the condition was met.
            if(count >= 3)
            {
                // If an alignment is found then one of the numbers in the alignment
                // will be swaped for a random one.
                for(int l = 0; l < count; l++)
                {
                    // Get a random number in the interval of the alignment.
                    swapIndex = rand() % count + 1;
                    // Get the element to swap using this random index.
                    swapAux = board[j + count - swapIndex][i];
                    // Generate a random number to put in the position of the item to swap.
                    board[j + count - swapIndex][i] = rand() % TILECOUNT + 1;
                    // Keep generating new numbers until it is different from the one causing the alignment.
                    while(board[j + count - swapIndex][i] == swapAux)
                        board[j + count - swapIndex][i] = rand() % TILECOUNT + 1;
                }
            }
        }
        alignmentCount = CountAlignments(board, boardSize);
    }
}

// Count available movements by realizing every possible move and counting alignments.
// If after doing every possible move there are alignments then user can still make alignments.
int CountAvailableMovements(int **board, int boardSize)
{
    int movements = 0, aux = 0, count = 0, flag = 1;
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            // This is for when the element is on the superior left corner.
            if(i == 0 && j == 0)
            {
                // Movement to the right
                // Move the element.
                aux = board[0][0];
                board[0][0] = board[0][1];
                board[0][1] = aux;
                // Count alignments made by this movement.
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                // Return element to its original place.
                aux = board[0][0];
                board[0][0] = board[0][1];
                board[0][1] = aux;
                // Movement to the bottom
                aux = board[0][0];
                board[0][0] = board[1][0];
                board[1][0] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[0][0];
                board[0][0] = board[1][0];
                board[1][0] = aux;
            }
            // This for when the element is on the superior right corner.
            else if(i == 0 && j == boardSize - 1)
            {
                // Movement to the left.
                aux = board[0][boardSize - 1];
                board[0][boardSize - 1] = board[0][boardSize - 2];
                board[0][boardSize - 2] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[0][boardSize - 1];
                board[0][boardSize - 1] = board[0][boardSize - 2];
                board[0][boardSize - 2] = aux;
                // Movement to the bottom.
                aux = board[0][boardSize - 1];
                board[0][boardSize - 1] = board[1][boardSize - 1];
                board[1][boardSize - 1] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[0][boardSize - 1];
                board[0][boardSize - 1] = board[1][boardSize - 1];
                board[1][boardSize - 1] = aux;
            }
            // This for when the element is on the inferior left corner.
            else if(i == boardSize - 1 && j == 0)
            {
                // Movement to the top.
                aux = board[boardSize - 1][0];
                board[boardSize - 1][0] = board[boardSize - 2][0];
                board[boardSize - 2][0] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[boardSize - 1][0];
                board[boardSize - 1][0] = board[boardSize - 2][0];
                board[boardSize - 2][0] = aux;
                // Movement to the right
                aux = board[boardSize - 1][0];
                board[boardSize - 1][0] = board[boardSize - 1][1];
                board[boardSize - 1][1] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[boardSize - 1][0];
                board[boardSize - 1][0] = board[boardSize - 1][1];
                board[boardSize - 1][1] = aux;
            }
            // This for when the element is on the inferior right corner.
            else if(i == boardSize - 1 && j == boardSize - 1)
            {
                // Movement to the top.
                aux = board[boardSize - 1][boardSize - 1];
                board[boardSize - 1][boardSize - 1] = board[boardSize - 2][boardSize - 1];
                board[boardSize - 2][boardSize - 1] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[boardSize - 1][boardSize - 1];
                board[boardSize - 1][boardSize - 1] = board[boardSize - 2][boardSize - 1];
                board[boardSize - 2][boardSize - 1] = aux;
                // Movement to the left.
                aux = board[boardSize - 1][boardSize - 1];
                board[boardSize - 1][boardSize - 1] = board[boardSize - 1][boardSize - 2];
                board[boardSize - 1][boardSize - 2] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[boardSize - 1][boardSize - 1];
                board[boardSize - 1][boardSize - 1] = board[boardSize - 1][boardSize - 2];
                board[boardSize - 1][boardSize - 2] = aux;
            }
            // This for every element on the top limit of the board.
            else if(i == 0)
            {
                // Movement to the right.
                aux = board[0][j];
                board[0][j] = board[0][j + 1];
                board[0][j + 1] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[0][j];
                board[0][j] = board[0][j + 1];
                board[0][j + 1] = aux;
                // Movement to the left.
                aux = board[0][j];
                board[0][j] = board[0][j - 1];
                board[0][j - 1] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[0][j];
                board[0][j] = board[0][j - 1];
                board[0][j - 1] = aux;
                // Movement to the bottom.
                aux = board[0][j];
                board[0][j] = board[1][j];
                board[1][j] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[0][j];
                board[0][j] = board[1][j];
                board[1][j] = aux;
            }
            // This for every element on the left limit of the board
            else if(j == 0)
            {
                // Movement to the top.
                aux = board[i][0];
                board[i][0] = board[i - 1][0];
                board[i - 1][0] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[i][0];
                board[i][0] = board[i - 1][0];
                board[i - 1][0] = aux;
                // Movement to the right
                aux = board[i][0];
                board[i][0] = board[i][1];
                board[i][1] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[i][0];
                board[i][0] = board[i][1];
                board[i][1] = aux;
                // Movement to the bottom.
                aux = board[i][0];
                board[i][0] = board[i + 1][0];
                board[i + 1][0] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[i][0];
                board[i][0] = board[i + 1][0];
                board[i + 1][0] = aux;
            }
            // This for every element on the bottom limit of the board.
            else if(i == boardSize - 1)
            {
                // Movement to the left.
                aux = board[boardSize - 1][j];
                board[boardSize - 1][j] = board[boardSize - 1][j - 1];
                board[boardSize - 1][j - 1] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[boardSize - 1][j];
                board[boardSize - 1][j] = board[boardSize - 1][j - 1];
                board[boardSize - 1][j - 1] = aux;
                // Movement to the top.
                aux = board[boardSize - 1][j];
                board[boardSize - 1][j] = board[boardSize - 2][j];
                board[boardSize - 2][j] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[boardSize - 1][j];
                board[boardSize - 1][j] = board[boardSize - 2][j];
                board[boardSize - 2][j] = aux;
                // Movement to the right.
                aux = board[boardSize - 1][j];
                board[boardSize - 1][j] = board[boardSize - 1][j + 1];
                board[boardSize - 1][j + 1] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[boardSize - 1][j];
                board[boardSize - 1][j] = board[boardSize - 1][j + 1];
                board[boardSize - 1][j + 1] = aux;

            }
            // This for every element on the right limit of the board.
            else if(j == boardSize - 1)
            {
                // Movement to the bottom.
                aux = board[i][boardSize - 1];
                board[i][boardSize - 1] = board[i + 1][boardSize - 1];
                board[i + 1][boardSize - 1] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[i][boardSize - 1];
                board[i][boardSize - 1] = board[i + 1][boardSize - 1];
                board[i + 1][boardSize - 1] = aux;
                // Movement to the left.
                aux = board[i][boardSize - 1];
                board[i][boardSize - 1] = board[i][boardSize - 2];
                board[i][boardSize - 2] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[i][boardSize - 1];
                board[i][boardSize - 1] = board[i][boardSize - 2];
                board[i][boardSize - 2] = aux;
                // Movement to the top.
                aux = board[i][boardSize - 1];
                board[i][boardSize - 1] = board[i - 1][boardSize - 1];
                board[i - 1][boardSize - 1] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[i][boardSize - 1];
                board[i][boardSize - 1] = board[i - 1][boardSize - 1];
                board[i - 1][boardSize - 1] = aux;
            }
            // This for every other element: elements that can move to all directions.
            else
            {
                // Movement to the right.
                aux = board[i][j];
                board[i][j] = board[i][j + 1];
                board[i][j + 1] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[i][j];
                board[i][j] = board[i][j + 1];
                board[i][j + 1] = aux;
                // Movement to the left.
                aux = board[i][j];
                board[i][j] = board[i][j - 1];
                board[i][j - 1] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[i][j];
                board[i][j] = board[i][j - 1];
                board[i][j - 1] = aux;
                // Movement to the top.
                aux = board[i][j];
                board[i][j] = board[i - 1][j];
                board[i - 1][j] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[i][j];
                board[i][j] = board[i - 1][j];
                board[i - 1][j] = aux;
                // Movement to the bottom.
                aux = board[i][j];
                board[i][j] = board[i + 1][j];
                board[i + 1][j] = aux;
                count = CountAlignments(board, boardSize);
                if(count > 0)
                    movements++;
                aux = board[i][j];
                board[i][j] = board[i + 1][j];
                board[i + 1][j] = aux;
            }
        }
    }

    // Since there are two ways to make each alignment, we divide the count by two.
    return movements / 2;
}
// Delete alignment by generating a random number for each number in the alignment. But the places are 
// not filled with these numbers, the numbers are displaced by the numbers in the top of them.
// In a sense the numbers 'fall' for each column the alignment touches.
void DeleteAlignment(int **board, int boardSize, int i, int j, char direction, int count)
{
    int aux = 0, k = i - 1, r = (direction == 'V') ? i + count - 1 : i;
    // Horizontal alignment.
    if(direction == 'H')
    {
        // Iterate over alignment elements.
        for(int p = 0; p < count; p++)
        {
            k = i - 1;
            r = i;
            while(r >= 0)
            {
                // For each element in the top of the alignment element we are going to displace it
                // to the bottom.
                if(k >= 0)
                {
                    board[r][j + p] = board[k][j + p];
                }
                // When the top is reached, generate a random number and place it there.
                else
                {
                    board[r][j + p] = rand() % TILECOUNT + 1;
                }
                k--;
                r--;
            }
        }
    }
    // Vertical alignment.
    else if(direction == 'V')
    {
        // This one is simpler since all elements displaced are in just one column
        while(r >= 0)
        {
            // Displace to the bottom.
            if(k >= 0)
            {
                board[r][j] = board[k][j];
            }
            // Put a random number in the top.
            else
            {
                board[r][j] = rand() % TILECOUNT + 1;
            }
            k--;
            r--;
        }
    }
}
// When a second alignment is found as a chain reaction from a first alignment the full line
// (column) is deleted.
void DeleteCompleteLine(int **board, int boardSize, int i, int j, char direction)
{
    // Horizontal alignment.
    if(direction == 'H')
    {
        for(int r = 0; r < boardSize; r++)
        {
            board[i][r] = rand() % TILECOUNT + 1;
        }
    }
    // Vertical alignment.
    else
    {
        for(int k = 0; k < boardSize; k++)
        {
            board[k][j] = rand()% TILECOUNT + 1;
        }
    }
}
// This searches for the alignment start and end to displace the elements from the top.
int SearchAlignmentCoordinate(int **board, int boardSize, int isChainReaction)
{
    char direction[boardSize];
    int j = 0, r = 0, count = 0, n = 0, x = 0;
    int alignmentCount = 0;
    // Horizontal alignments.
    for(int i = 0; i < boardSize; i++)
    {
        count = 0;
        j = 0;
        r = 0;
        // Same procedure than before to find alignments.
        while((j + r) < boardSize)
        {
            if(board[i][j] == board[i][j + r])
            {
                count++;
            }
            else
            {
                if(count >= 3)
                {
                    // When alignment is found then alignment is deleted.
                    n++;
                    // When a second alignment is found as a result of a first one a chain reaction is
                    // triggered that deletes the complete line where the alignment is located.
                    if(isChainReaction)
                        DeleteCompleteLine(board, boardSize, i, j, 'H');
                    else
                        DeleteAlignment(board, boardSize, i, j, 'H', count);
                    return count;
                }
                j += count;
                count = 0;
                r = -1;
            }
            r++;
        }
        if(count >= 3)
        {
            n++;
            if(isChainReaction)
                DeleteCompleteLine(board, boardSize, i, j, 'H');
            else
                DeleteAlignment(board, boardSize, i, j, 'H', count);
            return count;
        }
    }
    // Vertical alignments.
    for(int i = 0; i < boardSize; i++)
    {
        count = 0;
        j = 0;
        r = 0;
        while((j + r) < boardSize)
        {
            if(board[j][i] == board[j + r][i])
            {
                count++;
            }
            else
            {
                if(count >= 3)
                {
                    n++;
                    if(isChainReaction)
                        DeleteCompleteLine(board, boardSize, j, i, 'V');
                    else
                        DeleteAlignment(board, boardSize, j, i, 'V', count);
                    return count;
                }
                j += count;
                count = 0;
                r = -1;
            }
            r++;
        }
        if(count >= 3)
        {
            n++;
            if(isChainReaction)
                DeleteCompleteLine(board, boardSize, j, i, 'V');
            else
                DeleteAlignment(board, boardSize, j, i, 'V', count);
            return count;
        }
    }
}
// Validate if movement is valid by making it and counting alignments made by the movement.
bool ValidateMovement(int **board, int boardSize, int x1, int y1, int x2, int y2)
{
    int aux = board[x1][y1];
    board[x1][y1] = board[x2][y2];
    board[x2][y2] = aux;
    if(CountAlignments(board, boardSize) > 0)
        return true;
    aux = board[x1][y1];
    board[x1][y1] = board[x2][y2];
    board[x2][y2] = aux;
    return false;
}
int main()
{
    int boardSize, score = 0, movements = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    cout<<"Welcome to the three-matching game. The goal is to match three numbers to eliminate them from the board."<<endl;
    cout<<"The game ends when there are no more valid movements available in the board. A valid movement is moving two numbers"<<endl;
    cout<<"to form a three or more match of numbers"<<endl;
    cout<<"Board's size will be nxn (minimum: 4x4), enter n:"<<endl;
    cin>>boardSize;
    while(boardSize < 4)
    {
        cout<<"Error, invalid size for board, enter a size bigger than 3"<<endl;
        cin>>boardSize;
    }
    // Allocate memory for the board
    int **board = (int**)malloc(boardSize*boardSize*sizeof(int*));
    for (int i=0; i<boardSize; i++)
        board[i] = (int*)malloc(boardSize*sizeof(int));
    // Initialize a random board
    Initialize(board,boardSize);

    // The game stops when no more valid movemenets are available, this is,
    // when no movement can be made to make an aligment (a match).
    while(CountAvailableMovements(board, boardSize) > 0)
    {
        cout<<"board: "<<endl;
        Show(board, boardSize);
        cout<<endl;
        cout<<"Enter coordinates of elements to swap (consider first element is element (0,0))"<<endl;
        cout<<"Enter a -1 if you want to exit: "<<endl;
        cout<<"X1: "; cin>>x1;
        cout<<"Y1: "; cin>>y1;
        cout<<"X2: "; cin>>x2;
        cout<<"Y2: "; cin>>y2;
        if(x1 == -1 || x2 == -1 || y1 == -1 || y2 == -1)
        {
            break;
        }
        // Validate if movement makes a match
        if(ValidateMovement(board, boardSize, y1, x1, y2, x2))
        {
            cout<<"Match found!: "<<endl;
            Show(board, boardSize);
            cout<<endl;
            Sleep(500);
            // Get the score of the alignment by finding alignment count
            score += SearchAlignmentCoordinate(board, boardSize, 0);
            cout<<"score: "<<score<<endl;
            // If there is another alignment than a chain reaction happens and the full line is deleted.
            while(CountAlignments(board, boardSize) > 0)
            {
                cout<<"Chain reaction!: "<<endl;
                Show(board, boardSize);
                cout<<endl;
                score += SearchAlignmentCoordinate(board, boardSize, 1);
            }
        }
        else
            cout<<"Invalid movement"<<endl;
    }
    Show(board, boardSize);
    cout<<"Game ended, your score: "<<score<<endl;



	system("PAUSE");
}
