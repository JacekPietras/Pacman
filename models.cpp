#include "models.h"
struct model_w_skladzie {
	char * filename;
	model3DS * model;
	struct model_w_skladzie *wsk;
};
struct model_w_skladzie* sklad_modeli = NULL;

void dodajModel(model3DS * _model, char* file_name)
{
	struct model_w_skladzie* tmp;
	tmp = (struct model_w_skladzie *) malloc(sizeof(struct model_w_skladzie));
	tmp->filename = (char *)malloc(strlen(file_name) + 1);
	strcpy(tmp->filename, file_name);
	tmp->model = _model;
	tmp->wsk = sklad_modeli;
	sklad_modeli = tmp;
}

model3DS * pobierzModel(char* file_name)
{
	struct model_w_skladzie* sklad_tmp = sklad_modeli;
	while (sklad_tmp) {
		if (!_stricmp(sklad_tmp->filename, file_name)) return sklad_tmp->model;
		char file_name_full[_MAX_PATH];
		strcpy(file_name_full, file_name);
		strcat(file_name_full, ".3ds");
		if (!_stricmp(sklad_tmp->filename, file_name_full)) return sklad_tmp->model;

		sklad_tmp = sklad_tmp->wsk;
	}
	return NULL;
}

void ladujModele()
{
	WIN32_FIND_DATA *fd;
	HANDLE fh;
	model3DS * model_tmp;
	char directory[_MAX_PATH];
	if (_getcwd(directory, _MAX_PATH) == NULL) return;
	strcat(directory, "\\data\\*.3ds");

	fd = (WIN32_FIND_DATA *)malloc(sizeof(WIN32_FIND_DATA));
	fh = FindFirstFile((LPCSTR)directory, fd);
	if (fh != INVALID_HANDLE_VALUE)
		do {
			if (fd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {	// katalogi ignorujemy
				if (FindNextFile(fh, fd)) continue; else break;
			}
			// ladowanie obiektu i dodanie do kontenera
			char filename[_MAX_PATH];
			strcpy(filename, "data\\");
			strcat(filename, fd->cFileName);
			model_tmp = new model3DS(filename, 1, false);
			dodajModel(model_tmp, fd->cFileName);
			printf("[3DS] Model '%s' stored\n", fd->cFileName);
		} while (FindNextFile(fh, fd));
}

void rysujModel(char * file_name, int tex_num)
{
	model3DS * model_tmp;
	if (model_tmp = pobierzModel(file_name))
		if (tex_num == -1)
			model_tmp->draw();
		else
			model_tmp->draw(tex_num, false);

}
