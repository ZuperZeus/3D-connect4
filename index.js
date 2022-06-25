window.addEventListener('DOMContentLoaded', () => {
    const tiles = [][][];
    let board = [][][];
    const temptiles = Array.from(document.querySelectorAll('.tile'));
    let count=0;
    for(let i=0; i<4;i++)
    {
        for(let j=0; j<4;j++)
        {
            for(let k=0; k<4;k++)
            {
                tiles[i][j][k]=temptiles[count];
                tiles[i][j][k].addEventListener('click', () => userAction(i,j,k);
                board[i][j][k]=0;
                count++;
            }
        }
    }
    const tiles = document.querySelectorAll('.display-player');
    const tiles = document.querySelectorAll('#human');
    const tiles = document.querySelectorAll('#ai');
    const tiles = document.querySelectorAll('.announcer');

    let currpl='X';
    let gameActive = true;
    const PXW='PLAYERX_WON';
    const POW='PLAYER)_WON';
    const TIE='TIE';

    const userAction = (i,j,k) => {

    }
    resetButton.addEventListener();
});
