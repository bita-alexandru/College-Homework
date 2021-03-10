package repo;

import entity.Album;
import entity.Artist;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import java.util.List;

public class AlbumRepository {
    private EntityManager entityManager;

    public AlbumRepository(EntityManagerFactory factory) {
        entityManager = factory.createEntityManager();
    }

    public void create(Album album) { // receives an entity and saves it into the database;
        entityManager.getTransaction().begin();
        entityManager.persist(album);
        entityManager.getTransaction().commit();
    }

    public Album findById(long id) { // returns an entity based on its primary key;
        return entityManager.find(Album.class, id);
    }

    public List<Album> findByName(String name) { // returns a list of entities that match a given name pattern. Use a named query in order to implement this method.
        return entityManager.createNamedQuery("Album.findByName").setParameter("name", name).getResultList();
    }

    public List<Album> findByArtist(Artist artist) {
        return entityManager.createNamedQuery("Album.findByArtist").setParameter("artistId", artist.getId()).getResultList();
    }
}
