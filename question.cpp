#include<stdio.h>
#include<cmath>
#include<string>
#include<stdlib.h>
#include<string.h>

//定义树
typedef struct tree {
	bool yes;//是否被否定
	char link;//联结词
	struct tree* left1 = NULL;//左侧树
	struct tree* right1 = NULL;//左侧命题变项
	struct unit* left2 = NULL;//右侧树
	struct unit* right2 = NULL;//右侧命题变项
	struct tree* up = NULL;//上侧树
}tree;
//定义命题变项
typedef struct unit {
	bool yes;//是否被否定
	char name;//命题变项符号
}unit;
//初始化树
void start(tree* t) {
	t->yes = true;
	t->left1 = NULL;
	t->left2 = NULL;
	t->right1 = NULL;
	t->right2 = NULL;
	t->up = NULL;
	t->link = 'x';
}
//初始化命题变项
void ss(unit* u) {
	u->yes = true;
	u->name = 'x';
}
//读取命题并储存在树中
tree* read() {
	char str[1000];
	scanf("%s", str);
	tree* thetree = (tree*)malloc(sizeof(tree));
	start(thetree);
	int len = strlen(str);
	//循环
	for (int i = 0; i < len; i++) {
		//每次遍历前预处理，如果树左右已满就在上级建立新树
		while (((thetree->left1 != NULL) || (thetree->left2 != NULL)) && ((thetree->right1 != NULL) || (thetree->right2 != NULL))) {
			if (thetree->up != NULL) {
				thetree = thetree->up;
			}
			else {
				tree* a = (tree*)malloc(sizeof(tree));
				start(a);
				a->left1 = thetree;
				thetree->up = a;
				thetree = a;
			}
		}
		//读取命题变项
		if (str[i] <= 'Z' && str[i] >= 'A') {
			unit* a = (unit*)malloc(sizeof(unit));
			a->yes = true;
			a->name = str[i];
			if ((thetree->left1 == NULL) && (thetree->left2 == NULL)) {
				thetree->left2 = a;
			}
			else {
				thetree->right2 = a;
			}
			continue;
		}
		//读取联结词
		else if (str[i] >= '1' && str[i] <= '4') {
			thetree->link = str[i];
			continue;
		}
		//读取否定
		else if (str[i] == '0') {
			//双重否定
			if (str[i + 1] == '0') {
				thetree->yes = true;
				i++;
			}
			//命题变项的否定
			else if (str[i + 1] <= 'Z' && str[i + 1] >= 'A') {
				unit* a = (unit*)malloc(sizeof(unit));
				a->yes = false;
				a->name = str[i + 1];
				if ((thetree->left1 == NULL) && (thetree->left2 == NULL)) {
					thetree->left2 = a;
				}
				else {
					thetree->right2 = a;
				}
				i++;
			}
			//树的否定
			else {
				tree* a = (tree*)malloc(sizeof(tree));
				start(a);
				a->yes = false;
				a->up = thetree;
				if ((thetree->left1 == NULL) && (thetree->left2 == NULL)) {
					thetree->left1 = a;
				}
				else {
					thetree->right1 = a;
				}
				i++;
				thetree = a;
			}
			//对于否定树，直接读取了两个字符，需要快进至下次遍历
			continue;
		}
		//读取左括号，建立新的子树
		else if (str[i] == '(') {
			tree* a = (tree*)malloc(sizeof(tree));
			start(a);
			a->yes = true;
			a->up = thetree;
			if ((thetree->left1 == NULL) && (thetree->left2 == NULL)) {
				thetree->left1 = a;
			}
			else {
				thetree->right1 = a;
			}
			thetree = a;
			continue;
		}
	}
	//返回最上级树
	if(thetree->link == 'x'){
		return thetree->left1;
	}
	else{
		while (true) {
			if(thetree->up != NULL){
				if(thetree->up->link != 'x'){
					thetree = thetree->up;
					continue;
				}
				else{
					break;
				}
			}
			else {
				break;
			}
		}
	}
	return thetree;
}
//王浩函数
void wanghao(tree* mt) {

	//初始化
	tree* l[100][100];//储存前件每个式子的树
	tree* r[100][100];//储存后件每个式子的树
	unit* lu[100][100];//储存前件每个式子的命题变项
	unit* ru[100][100];//储存后件每个式子的命题变项
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			l[i][j] = (tree*)malloc(sizeof(sizeof(tree)));
			r[i][j] = (tree*)malloc(sizeof(sizeof(tree)));
			lu[i][j] = (unit*)malloc(sizeof(sizeof(unit)));
			ru[i][j] = (unit*)malloc(sizeof(sizeof(unit)));
			start(l[i][j]);
			start(r[i][j]);
			ss(lu[i][j]);
			ss(ru[i][j]);
		}
	}
	int a[100] = { 0 };//储存前件每个式子树的个数
	int b[100] = { 0 };//储存后件每个式子树的个数
	int aa[100] = { 0 };//储存前件每个式子未处理树的个数
	int bb[100] = { 0 };//储存后件每个式子未处理树的个数
	int au[100] = { 0 };//储存前件每个式子命题变项的个数
	int bu[100] = { 0 };//储存后件每个式子命题变项的个数
	int num = 1;//储存式子个数
	r[0][0] = mt;
	b[0] = 1;
	bb[0] = 1;
	//遍历
	int nowa = 0;//记录当前遍历到了下标为nowa的式子
	bool bigwh = true;
	while (nowa < num) {
		bool wh = false;
		while (!(aa[nowa] == 0 && bb[nowa] == 0)) {
			//处理后件
			int nowb = b[nowa] - bb[nowa];//记录当前遍历到了后件式子中下标为nowb的树
			while (nowb < b[nowa]) {
				//处理后件否定
				if (r[nowa][nowb]->yes == false) {
					r[nowa][nowb]->yes = true;
					l[nowa][a[nowa]] = r[nowa][nowb];
					a[nowa]++;
					aa[nowa]++;
					bb[nowa]--;
				}
				//处理后件析取
				else if (r[nowa][nowb]->link == '1') {
					if (r[nowa][nowb]->left1 != NULL) {
						r[nowa][b[nowa]] = r[nowa][nowb]->left1;
						b[nowa]++;
						bb[nowa]++;
					}
					else {
						ru[nowa][bu[nowa]] = r[nowa][nowb]->left2;
						bu[nowa]++;
					}
					if (r[nowa][nowb]->right1 != NULL) {
						r[nowa][b[nowa]] = r[nowa][nowb]->right1;
						b[nowa]++;
						bb[nowa]++;
					}
					else {
						ru[nowa][bu[nowa]] = r[nowa][nowb]->right2;
						bu[nowa]++;
					}
					bb[nowa]--;
				}
				//处理后件合取
				else if (r[nowa][nowb]->link == '2') {
					int t1, t2;
					if (r[nowa][nowb]->left1 != NULL) {
						r[nowa][b[nowa]] = r[nowa][nowb]->left1;
						t1 = b[nowa] + 1;
						t2 = bu[nowa];
					}
					else {
						ru[nowa][bu[nowa]] = r[nowa][nowb]->left2;
						t1 = b[nowa];
						t2 = bu[nowa] + 1;
					}
					for (int i = 0; i < t1; i++) {
						r[num][i]->left1 = r[nowa][i]->left1;
						r[num][i]->left2 = r[nowa][i]->left2;
						r[num][i]->right1 = r[nowa][i]->right1;
						r[num][i]->right2 = r[nowa][i]->right2;
						r[num][i]->link = r[nowa][i]->link;
						l[num][i]->yes = r[nowa][i]->yes;
					}
					for (int i = 0; i < a[nowa]; i++) {
						l[num][i]->left1 = l[nowa][i]->left1;
						l[num][i]->left2 = l[nowa][i]->left2;
						l[num][i]->right1 = l[nowa][i]->right1;
						l[num][i]->right2 = l[nowa][i]->right2;
						l[num][i]->link = l[nowa][i]->link;
						l[num][i]->yes = l[nowa][i]->yes;
					}
					for (int i = 0; i < t2; i++) {
						ru[num][i]->name = ru[nowa][i]->name;
						ru[num][i]->yes = ru[nowa][i]->yes;
					}
					for (int i = 0; i < au[nowa]; i++) {
						lu[num][i]->name = lu[nowa][i]->name;
						lu[num][i]->yes = lu[nowa][i]->yes;
					}
					a[num] = a[nowa];
					aa[num] = aa[nowa];
					au[num] = au[nowa];
					b[num] = t1;
					bb[num] = bb[nowa] + t1 - b[nowa] - 1;
					bu[num] = t2;
					num++;
					if (r[nowa][nowb]->right1 != NULL) {
						r[nowa][b[nowa]] = r[nowa][nowb]->right1;
						t1 = b[nowa] + 1;
						t2 = bu[nowa];
					}
					else {
						ru[nowa][bu[nowa]] = r[nowa][nowb]->right2;
						t1 = b[nowa];
						t2 = bu[nowa] + 1;
					}
					for (int i = 0; i < t1; i++) {
						r[num][i]->left1 = r[nowa][i]->left1;
						r[num][i]->left2 = r[nowa][i]->left2;
						r[num][i]->right1 = r[nowa][i]->right1;
						r[num][i]->right2 = r[nowa][i]->right2;
						r[num][i]->link = r[nowa][i]->link;
						l[num][i]->yes = r[nowa][i]->yes;
					}
					for (int i = 0; i < a[nowa]; i++) {
						l[num][i]->left1 = l[nowa][i]->left1;
						l[num][i]->left2 = l[nowa][i]->left2;
						l[num][i]->right1 = l[nowa][i]->right1;
						l[num][i]->right2 = l[nowa][i]->right2;
						l[num][i]->link = l[nowa][i]->link;
						l[num][i]->yes = l[nowa][i]->yes;
					}
					for (int i = 0; i < t2; i++) {
						ru[num][i]->name = ru[nowa][i]->name;
						ru[num][i]->yes = ru[nowa][i]->yes;
					}
					for (int i = 0; i < au[nowa]; i++) {
						lu[num][i]->name = lu[nowa][i]->name;
						lu[num][i]->yes = lu[nowa][i]->yes;
					}
					a[num] = a[nowa];
					aa[num] = aa[nowa];
					au[num] = au[nowa];
					b[num] = t1;
					bb[num] = bb[nowa] + t1 - b[nowa] - 1;
					bu[num] = t2;
					num++;
					nowa++;
					break;
				}
				//处理后件蕴含
				else if (r[nowa][nowb]->link == '3') {
					if (r[nowa][nowb]->left1 != NULL) {
						l[nowa][a[nowa]] = r[nowa][nowb]->left1;
						a[nowa]++;
						aa[nowa]++;
					}
					else {
						lu[nowa][au[nowa]] = r[nowa][nowb]->left2;
						au[nowa]++;
					}
					if (r[nowa][nowb]->right1 != NULL) {
						r[nowa][b[nowa]] = r[nowa][nowb]->right1;
						b[nowa]++;
						bb[nowa]++;
					}
					else {
						ru[nowa][bu[nowa]] = r[nowa][nowb]->right2;
						bu[nowa]++;
					}
					bb[nowa]--;
				}
				nowb++;
			}
			//处理前件
			int nowc = a[nowa] - aa[nowa];//记录当前遍历到了前件式子中下标为nowc的树
			while (nowc < a[nowa]) {
				//处理前件否定
				if (l[nowa][nowc]->yes == false) {
					l[nowa][nowc]->yes = true;
					r[nowa][a[nowa]] = l[nowa][nowc];
					b[nowa]++;
					bb[nowa]++;
					aa[nowa]--;
				}
				//处理前件析取
				else if (l[nowa][nowc]->link == '1') {
					int t1, t2;
					if (l[nowa][nowc]->left1 != NULL) {
						l[nowa][a[nowa]] = l[nowa][nowc]->left1;
						t1 = a[nowa] + 1;
						t2 = au[nowa];
					}
					else {
						lu[nowa][au[nowa]] = l[nowa][nowc]->left2;
						t1 = a[nowa];
						t2 = au[nowa] + 1;
					}
					for (int i = 0; i < t1; i++) {
						l[num][i]->left1 = l[nowa][i]->left1;
						l[num][i]->left2 = l[nowa][i]->left2;
						l[num][i]->right1 = l[nowa][i]->right1;
						l[num][i]->right2 = l[nowa][i]->right2;
						l[num][i]->link = l[nowa][i]->link;
					}
					for (int i = 0; i < b[nowa]; i++) {
						r[num][i]->left1 = r[nowa][i]->left1;
						r[num][i]->left2 = r[nowa][i]->left2;
						r[num][i]->right1 = r[nowa][i]->right1;
						r[num][i]->right2 = r[nowa][i]->right2;
						r[num][i]->link = r[nowa][i]->link;
					}
					for (int i = 0; i < t2; i++) {
						lu[num][i]->name = lu[nowa][i]->name;
						lu[num][i]->yes = lu[nowa][i]->yes;
					}
					for (int i = 0; i < bu[nowa]; i++) {
						ru[num][i]->name = ru[nowa][i]->name;
						ru[num][i]->yes = ru[nowa][i]->yes;
					}
					b[num] = b[nowa];
					bb[num] = bb[nowa];
					bu[num] = bu[nowa];
					a[num] = t1;
					aa[num] = aa[nowa] + t1 - a[nowa] - 1;
					au[num] = t2;
					num++;
					if (l[nowa][nowc]->right1 != NULL) {
						l[nowa][a[nowa]] = l[nowa][nowc]->right1;
						t1 = a[nowa] + 1;
						t2 = au[nowa];
					}
					else {
						lu[nowa][au[nowa]] = l[nowa][nowc]->right2;
						t1 = a[nowa];
						t2 = au[nowa] + 1;
					}
					for (int i = 0; i < t1; i++) {
						l[num][i]->left1 = l[nowa][i]->left1;
						l[num][i]->left2 = l[nowa][i]->left2;
						l[num][i]->right1 = l[nowa][i]->right1;
						l[num][i]->right2 = l[nowa][i]->right2;
						l[num][i]->link = l[nowa][i]->link;
					}
					for (int i = 0; i < b[nowa]; i++) {
						r[num][i]->left1 = r[nowa][i]->left1;
						r[num][i]->left2 = r[nowa][i]->left2;
						r[num][i]->right1 = r[nowa][i]->right1;
						r[num][i]->right2 = r[nowa][i]->right2;
						r[num][i]->link = r[nowa][i]->link;
					}
					for (int i = 0; i < t2; i++) {
						lu[num][i]->name = lu[nowa][i]->name;
						lu[num][i]->yes = lu[nowa][i]->yes;
					}
					for (int i = 0; i < bu[nowa]; i++) {
						ru[num][i]->name = ru[nowa][i]->name;
						ru[num][i]->yes = ru[nowa][i]->yes;
					}
					b[num] = b[nowa];
					bb[num] = bb[nowa];
					bu[num] = bu[nowa];
					a[num] = t1;
					aa[num] = aa[nowa] + t1 - a[nowa] - 1;
					au[num] = t2;
					num++;
					nowa++;
					break;
				}
				//处理前件合取
				else if (l[nowa][nowc]->link == '2') {
					if (l[nowa][nowc]->left1 != NULL) {
						l[nowa][a[nowa]] = l[nowa][nowc]->left1;
						a[nowa]++;
						aa[nowa]++;
					}
					else {
						lu[nowa][au[nowa]] = l[nowa][nowc]->left2;
						au[nowa]++;
					}
					if (l[nowa][nowc]->right1 != NULL) {
						l[nowa][a[nowa]] = l[nowa][nowb]->right1;
						a[nowa]++;
						aa[nowa]++;
					}
					else {
						lu[nowa][au[nowa]] = l[nowa][nowc]->right2;
						bu[nowa]++;
					}
					aa[nowa]--;
				}
				//处理前件蕴含
				else if (l[nowa][nowc]->link == '3') {
					int t1, t2;
					if (l[nowa][nowc]->left1 != NULL) {
						r[nowa][b[nowa]] = l[nowa][nowc]->left1;
						t1 = b[nowa] + 1;
						t2 = bu[nowa];
					}
					else {
						ru[nowa][bu[nowa]] = l[nowa][nowc]->left2;
						t1 = b[nowa];
						t2 = bu[nowa] + 1;
					}
					for (int i = 0; i < t1; i++) {
						r[num][i]->left1 = r[nowa][i]->left1;
						r[num][i]->left2 = r[nowa][i]->left2;
						r[num][i]->right1 = r[nowa][i]->right1;
						r[num][i]->right2 = r[nowa][i]->right2;
						r[num][i]->link = r[nowa][i]->link;
					}
					for (int i = 0; i < a[nowa]; i++) {
						l[num][i]->left1 = l[nowa][i]->left1;
						l[num][i]->left2 = l[nowa][i]->left2;
						l[num][i]->right1 = l[nowa][i]->right1;
						l[num][i]->right2 = l[nowa][i]->right2;
						l[num][i]->link = l[nowa][i]->link;
					}
					for (int i = 0; i < t2; i++) {
						ru[num][i]->name = ru[nowa][i]->name;
						ru[num][i]->yes = ru[nowa][i]->yes;
					}
					for (int i = 0; i < au[nowa]; i++) {
						lu[num][i]->name = lu[nowa][i]->name;
						lu[num][i]->yes = lu[nowa][i]->yes;
					}
					a[num] = a[nowa];
					aa[num] = aa[nowa] - 1;
					au[num] = au[nowa];
					b[num] = t1;
					bb[num] = bb[nowa] + t1 - b[nowa];
					bu[num] = t2;
					num++;
					if (l[nowa][nowc]->right1 != NULL) {
						l[nowa][a[nowa]] = l[nowa][nowc]->right1;
						t1 = a[nowa] + 1;
						t2 = au[nowa];
					}
					else {
						lu[nowa][au[nowa]] = l[nowa][nowc]->right2;
						t1 = a[nowa];
						t2 = au[nowa] + 1;
					}
					for (int i = 0; i < b[nowa]; i++) {
						r[num][i]->left1 = r[nowa][i]->left1;
						r[num][i]->left2 = r[nowa][i]->left2;
						r[num][i]->right1 = r[nowa][i]->right1;
						r[num][i]->right2 = r[nowa][i]->right2;
						r[num][i]->link = r[nowa][i]->link;
					}
					for (int i = 0; i < t1; i++) {
						l[num][i]->left1 = l[nowa][i]->left1;
						l[num][i]->left2 = l[nowa][i]->left2;
						l[num][i]->right1 = l[nowa][i]->right1;
						l[num][i]->right2 = l[nowa][i]->right2;
						l[num][i]->link = l[nowa][i]->link;
					}
					for (int i = 0; i < bu[nowa]; i++) {
						ru[num][i]->name = ru[nowa][i]->name;
						ru[num][i]->yes = ru[nowa][i]->yes;
					}
					for (int i = 0; i < t2; i++) {
						lu[num][i]->name = lu[nowa][i]->name;
						lu[num][i]->yes = lu[nowa][i]->yes;
					}
					a[num] = t1;
					aa[num] = aa[nowa] + t1 - a[nowa] - 1;
					au[num] = t2;
					b[num] = b[nowa];
					bb[num] = bb[nowa];
					bu[num] = bu[nowa];
					num++;
					nowa++;
					break;
				}
				nowc++;
			}
		}
		int temp[130][2] = {0};
		for (int i = 0; i < au[nowa]; i++) {
			if (lu[nowa][i]->yes == true)temp[lu[nowa][i]->name][0] = 1;
			else if (lu[nowa][i]->yes == false)temp[lu[nowa][i]->name][1] = 1;
		}
		for (int i = 0; i < bu[nowa]; i++) {
			if (ru[nowa][i]->yes == true)temp[ru[nowa][i]->name][1] = 1;
			else if (ru[nowa][i]->yes == false)temp[ru[nowa][i]->name][0] = 1;
		}
		for (int i = 'A'; i <= 'Z'; i++) {
			if (temp[i][0] == 1 && temp[i][1] == 1) {
				wh = true;
				break;
			}
		}
		//返回式子真假
		if (wh == false) {
			bigwh = false;
			break;
		}
		nowa++;
	}
	//返回最终结果
	if (bigwh == true)printf("TRUE");
	else printf("FALSE");
}
int main() {
	tree* Tree = read();
	wanghao(Tree);
	return 0;
}