package app;

import entity.Album;
import entity.Artist;
import repo.AlbumRepository;
import repo.ArtistRepository;
import util.PersistenceUtil;

import java.util.List;

public class AlbumManager {
    public static void main(String[] args) {
        ArtistRepository artistRepository = new ArtistRepository(PersistenceUtil.getInstance().getFactory());
        AlbumRepository albumRepository = new AlbumRepository(PersistenceUtil.getInstance().getFactory());

        artistRepository.create(new Artist("Nevastuica Rock","Zimbabwe"));
        albumRepository.create(new Album("Trage-mi degetul",1,2013L));

        Artist artist = artistRepository.findById(1L);
        List<Artist> artists = artistRepository.findByName("Nevastuica Rock");

        Album album = albumRepository.findById(1L);
        List<Album> albums1 = albumRepository.findByName("Trage-mi degetul");
        List<Album> albums2 = albumRepository.findByArtist(artist);

        System.out.println(artist);
        for(Artist currArtist : artists) {
            System.out.println(currArtist);
        }

        System.out.println(album);
        for(Album currAlbum : albums1) {
            System.out.println(currAlbum);
        }
        for(Album currAlbum : albums2) {
            System.out.println(currAlbum);
        }

        PersistenceUtil.getInstance().getFactory().close();
    }
}
