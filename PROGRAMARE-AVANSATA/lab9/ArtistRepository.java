package repo;

import entity.Artist;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import java.util.List;

public class ArtistRepository {
    private EntityManager entityManager;

    public ArtistRepository(EntityManagerFactory factory) {
        entityManager = factory.createEntityManager();
    }

    public void create(Artist artist) { // receives an entity and saves it into the database;
        entityManager.getTransaction().begin();
        entityManager.persist(artist);
        entityManager.getTransaction().commit();
    }

    public Artist findById(long id) { // returns an entity based on its primary key;
        return entityManager.find(Artist.class, id);
    }

    public List<Artist> findByName(String name) { // returns a list of entities that match a given name pattern. Use a named query in order to implement this method.
        return entityManager.createNamedQuery("Artist.findByName").setParameter("name", name).getResultList();
    }
}
