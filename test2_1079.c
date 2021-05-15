int numTilePossibilities(char * tiles){
    int length = strlen(tiles);
    int k[26] = {0}, ans = 0;
    for(int i = 0; i < length; i++)
    {
        k[tiles[i] - 'A']++;
    }
     ans = dfs(k);
    return ans;
}

int dfs(int* G){
    int i = 0, sum = 0;
    for(i = 0; i < 26; i++)
    {
        if(G[i]==0)
            continue;
        G[i]--;
        sum++;
        sum += dfs(G);
        G[i]++;
    }
    return sum;
}
