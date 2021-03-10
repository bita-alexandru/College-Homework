package entity;

import javax.persistence.*;
import java.util.Objects;

@Entity
@Table(name = "ARTISTS", schema = "ALEX")
@NamedQueries({
        @NamedQuery(name = "Artist.findByName",
                query = "select artist from Artist artist where artist.name like :name")
})
public class Artist {
    private long id;
    private String name;
    private String country;

    public Artist(String name, String country) {
        this.name = name;
        this.country = country;
    }

    public Artist() {
        
    }

    @Id
    @Column(name = "ID")
    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    @Basic
    @Column(name = "NAME")
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Basic
    @Column(name = "COUNTRY")
    public String getCountry() {
        return country;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Artist that = (Artist) o;
        return id == that.id &&
                Objects.equals(name, that.name) &&
                Objects.equals(country, that.country);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, name, country);
    }

    @Override
    public String toString() {
        return name + " from " + country;
    }
}
