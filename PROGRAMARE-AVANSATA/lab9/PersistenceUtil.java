package util;

import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

public class PersistenceUtil {
    private static final PersistenceUtil instance = new PersistenceUtil();
    private EntityManagerFactory factory;

    private PersistenceUtil() {
        factory = Persistence.createEntityManagerFactory("MusicAlbumsPU");
    }

    public static PersistenceUtil getInstance() {
        return instance;
    }

    public EntityManagerFactory getFactory() {
        return factory;
    }
}