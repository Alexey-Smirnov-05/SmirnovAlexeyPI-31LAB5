#include "Header.h"

int main() {
    system("chcp 1251");
    setlocale(LC_ALL, "RUS");

    Playlist playlist;
    User user(&playlist);
    Volume volume;

    playlist.load_tracks_from_file("playlist.txt");

    int choice;
    while (1) {
        printf("Меню плеера:\n");
        printf("0. Добавить трек\n");
        printf("1. Изменить громкость\n");
        printf("2. Воспроизвести\n");
        printf("3. Пауза\n");
        printf("4. Следующий трек\n");
        printf("5. Предыдущий трек\n");
        printf("6. Удалить трек\n");
        printf("7. Просмотреть треки в плейлисте\n");
        printf("8. Выход\n");
        printf("Действие: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0: {
            Track song;
            printf("Введите название трека: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            char title[100];
            fgets(title, 100, stdin);
            title[strcspn(title, "\n")] = 0;
            song.setTitle(title);
            user.addSongToPlaylist(song);
            playlist.save_tracks_to_file("playlist.txt");
            break;
        }
        case 1: {
            int new_volume;
            printf("Введите громкость (0-100): ");
            scanf("%d", &new_volume);
            volume.changeVolume(new_volume);
            break;
        }
        case 2:
            if (playlist.getTotalNumberOfTracks() > 0) {
                Playback playback(&playlist, playlist.getCurrentTrack());
                playback.playSong();
            }
            else {
                printf("Нет треков в плейлисте\n");
            }
            break;
        case 3:
            if (playlist.getTotalNumberOfTracks() > 0) {
                Pause pause(&playlist);
                pause.pauseSong();
            }
            else {
                printf("Нет треков в плейлисте\n");
            }
            break;
        case 4:
            if (playlist.getTotalNumberOfTracks() > 0) {
                Skip skip(&playlist);
                skip.skipSong();
            }
            else {
                printf("Нет треков в плейлисте\n");
            }
            break;
        case 5:
            if (playlist.getTotalNumberOfTracks() > 0) {
                Previous previous(&playlist);
                previous.previousSong();
            }
            else {
                printf("Нет треков в плейлисте\n");
            }
            break;
        case 6: {
            if (playlist.getTotalNumberOfTracks() > 0) {
                int index;
                printf("Введите индекс трека для удаления: ");
                scanf("%d", &index);
                if (index >= 1 && index <= playlist.getTotalNumberOfTracks()) {
                    playlist.removeSong(index - 1);
                    playlist.save_tracks_to_file("playlist.txt"); // Сохраняем изменения в файле
                }
                else {
                    printf("Неверный индекс\n");
                }
            }
            else {
                printf("Нет треков в плейлисте\n");
            }
            break;
        }
        case 7:
            if (playlist.getTotalNumberOfTracks() > 0) {
                View view(&playlist);
                view.viewSongs();
            }
            else {
                printf("Нет треков в плейлисте\n");
            }
            break;
        case 8:
            return 0;
        default:
            printf("Ошибка выбора действия\n");
        }
        printf("\n\n");
    }
    return 0;
}