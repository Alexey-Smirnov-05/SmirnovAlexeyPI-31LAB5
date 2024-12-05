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
        printf("���� ������:\n");
        printf("0. �������� ����\n");
        printf("1. �������� ���������\n");
        printf("2. �������������\n");
        printf("3. �����\n");
        printf("4. ��������� ����\n");
        printf("5. ���������� ����\n");
        printf("6. ������� ����\n");
        printf("7. ����������� ����� � ���������\n");
        printf("8. �����\n");
        printf("��������: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0: {
            Track song;
            printf("������� �������� �����: ");
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
            printf("������� ��������� (0-100): ");
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
                printf("��� ������ � ���������\n");
            }
            break;
        case 3:
            if (playlist.getTotalNumberOfTracks() > 0) {
                Pause pause(&playlist);
                pause.pauseSong();
            }
            else {
                printf("��� ������ � ���������\n");
            }
            break;
        case 4:
            if (playlist.getTotalNumberOfTracks() > 0) {
                Skip skip(&playlist);
                skip.skipSong();
            }
            else {
                printf("��� ������ � ���������\n");
            }
            break;
        case 5:
            if (playlist.getTotalNumberOfTracks() > 0) {
                Previous previous(&playlist);
                previous.previousSong();
            }
            else {
                printf("��� ������ � ���������\n");
            }
            break;
        case 6: {
            if (playlist.getTotalNumberOfTracks() > 0) {
                int index;
                printf("������� ������ ����� ��� ��������: ");
                scanf("%d", &index);
                if (index >= 1 && index <= playlist.getTotalNumberOfTracks()) {
                    playlist.removeSong(index - 1);
                    playlist.save_tracks_to_file("playlist.txt"); // ��������� ��������� � �����
                }
                else {
                    printf("�������� ������\n");
                }
            }
            else {
                printf("��� ������ � ���������\n");
            }
            break;
        }
        case 7:
            if (playlist.getTotalNumberOfTracks() > 0) {
                View view(&playlist);
                view.viewSongs();
            }
            else {
                printf("��� ������ � ���������\n");
            }
            break;
        case 8:
            return 0;
        default:
            printf("������ ������ ��������\n");
        }
        printf("\n\n");
    }
    return 0;
}