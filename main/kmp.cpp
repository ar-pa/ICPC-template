int k = 0;
for(int i = 1; i < p.size(); i++){
	while(k && p[k] != p[i])  k = f[k];
	if(p[k] == p[i])  k++;
	f[i + 1] = k;
}
